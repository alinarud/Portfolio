//
//  PostChartViewController.swift
//  DeWash
//
//  Created by user on 02.04.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit
import Charts

public class BarValueFormatter : IValueFormatter {
    public func stringForValue(_ value: Double, entry: ChartDataEntry, dataSetIndex: Int, viewPortHandler: ViewPortHandler?) -> String {
        if (value == 0 || value <= 0.4) {
            return ""
        }
        
        return "\(Double(value))"
    }
}


class PostChartViewController: UIViewController {

    var controller: Controller?
    private var dewashData: DeWashDataStorage?
    
    @IBOutlet weak var barChart: BarChartView!
    @IBOutlet weak var periodFromTExtField: UITextField!
    @IBOutlet weak var periodToTextField: UITextField!
    @IBOutlet weak var resultTextField: UITextField!
    @IBOutlet weak var filterTextView: UITextField!
    
    private var fromPeriodDatePicker: UIDatePicker?
    private var toPeriodDatePicker: UIDatePicker?
    private var dateFrom: Date = Date()
    private var dateTo: Date = Date()
    private var token: String?
    private var updateTimer: Timer?
    private var barValueFormatter: BarValueFormatter = BarValueFormatter()
    private var barEntry: [BarChartDataEntry] = []
    var barEntryLabels: [String] = []
    public var barDataSet: BarChartDataSet = BarChartDataSet()
    var barData: BarChartData = BarChartData()
    var filterPicker: UIPickerView?
    var selectedFilter: Int = Constants.ChartFilter.spent_money
    var filters: [String] = [ NSLocalizedString("Chemistry consumption", comment: ""),
							  NSLocalizedString("Electricity consumption", comment: ""),
							  NSLocalizedString("Water consumption", comment: ""),
                              NSLocalizedString("Spent money", comment: ""),
							  NSLocalizedString("Working time", comment: "") ]
    var currentResultArray: Array<PackageResponse>?
   
    
    @IBAction func periodFromEditingBegin(_ sender: Any) {
        print("From editing began")
        if (self.periodFromTExtField.text!.isEmpty) {
           let dateFormat = DateFormatter()
           dateFormat.dateFormat = "dd/MM/yyyy"
           self.periodFromTExtField.text = dateFormat.string(from: Date())
        }
    }
    
    @IBAction func periodFromEditingEnded(_ sender: Any) {
        updateChart();
    }

    @IBAction func periodToEditingBegan(_ sender: Any) {
        if (self.periodToTextField.text!.isEmpty) {
            let dateFormat = DateFormatter()
            dateFormat.dateFormat = "dd/MM/yyyy"
            self.periodToTextField.text = dateFormat.string(from: Date())
        }
    }
    
    @IBAction func periodToEditingEnded(_ sender: Any) {
        updateChart();
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.filterTextView.text = filters[selectedFilter]
        
        // init datePickers
        initDateFromPicker()
        initDateToPicker()
        createModePickerView()
        createPickerToolBar()
        
        let dateFormat = DateFormatter()
        dateFormat.dateFormat = "dd/MM/yyyy"
        
        var dateComp = Calendar.current.dateComponents([.year, .month, .day, .hour, .minute, .second], from: self.dateFrom)
        dateComp.hour = 0
        dateComp.minute = 0
        dateComp.second = 0
        self.dateFrom = Calendar.current.date(from: dateComp) ?? Date()
 
        self.periodFromTExtField.text = dateFormat.string(from: self.dateFrom)
        self.periodToTextField.text = dateFormat.string(from: self.dateTo)

        updateChart()
   
        updateTimer = Timer.scheduledTimer(timeInterval: TimeInterval(Constants.UPDATE_TIMER), target: self, selector: #selector(updateData), userInfo: nil, repeats: true)
    }
    
    @objc
    func updateData() {
        updateChart()
    }
    
    private func updateControllerData() {
        let postId = controller?._id
        let str = "/" + (postId ?? "")
        let url = URL(string: Api.SERVER_URL + Api.CONTROLLER.URL_CONTROLLER_ID + str)!
        let session = URLSession.shared;
        var request = URLRequest(url: url);
        
        request.setValue(self.token, forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.setValue("application/json", forHTTPHeaderField: "Accept")
        request.httpMethod = "GET";
               
        let task = session.dataTask(with: request as URLRequest, completionHandler:
                                        { data, response, error in
            
        guard let data = data,
            let response = response as? HTTPURLResponse, error == nil else {                                              // check for fundamental networking error
             print("error", error ?? "Unknown error")
             return
         }

         guard (200 ... 299) ~= response.statusCode else {                    // check for http errors
             print("statusCode should be 2xx, but is \(response.statusCode)")
             print("response = \(response)")
             return
         }

         do {
            let decoder = JSONDecoder()
            let result = try decoder.decode(SetValueResponse.self, from: data)
             
            DispatchQueue.main.async {
                self.controller = result.controller
            }
               
                 
             } catch let err {
                 print("\nErr", err)
                 return;
             }
        })
        task.resume();
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        updateTimer?.invalidate()
    }
    
    private func initDateFromPicker() {
        self.fromPeriodDatePicker = UIDatePicker()

        if #available(iOS 13.4, *) {
            self.fromPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.fromPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.fromPeriodDatePicker?.preferredDatePickerStyle = .wheels
            self.fromPeriodDatePicker?.preferredDatePickerStyle = .wheels
        }
        
        self.fromPeriodDatePicker?.datePickerMode = .date
        self.fromPeriodDatePicker?.addTarget(self, action: #selector(PostChartViewController.fromPeriodDateChanged(datePicker:)), for: .valueChanged)

        let toolBar = UIToolbar(frame: CGRect(origin: .zero, size: CGSize(width: 100, height: 44.0)))
        toolBar.barStyle = UIBarStyle.default
        toolBar.isTranslucent = true
        toolBar.sizeToFit()

        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.frpmDonePicked))
        
        let cancelButton = UIBarButtonItem(title: NSLocalizedString("Cancel", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.cancelPicked))

        toolBar.setItems([cancelButton, spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true

        self.periodFromTExtField.inputView = self.fromPeriodDatePicker
        self.periodFromTExtField.inputAccessoryView = toolBar
    }
    
    private func initDateToPicker() {
        self.toPeriodDatePicker = UIDatePicker()
        if #available(iOS 13.4, *) {
            self.toPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.toPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.toPeriodDatePicker?.preferredDatePickerStyle = .wheels
            self.toPeriodDatePicker?.preferredDatePickerStyle = .wheels
        }
        
       self.toPeriodDatePicker?.datePickerMode = .date
       self.toPeriodDatePicker?.addTarget(self, action: #selector(PostChartViewController.toPeriodDateChanged(datePicker:)), for: .valueChanged)
           
        let toolBar = UIToolbar(frame: CGRect(origin: .zero, size: CGSize(width: 100, height: 44.0)))
        toolBar.barStyle = UIBarStyle.default
        toolBar.isTranslucent = true
        toolBar.sizeToFit()

        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.frpmDonePicked))
        
        let cancelButton = UIBarButtonItem(title: NSLocalizedString("Cancel", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.cancelPicked))

        toolBar.setItems([cancelButton, spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true

        self.periodToTextField.inputView = self.toPeriodDatePicker
        self.periodToTextField.inputAccessoryView = toolBar
    }
    
    @objc func cancelPicked() {
        view.endEditing(true)
    }
    
    public func setController(controller: Controller?, dewashData: DeWashDataStorage?) {
        self.controller = controller
        self.dewashData = dewashData
    }

    public func setToken(token: String?) {
        self.token = token
    }
    
    @objc func viewTapped(gestureRecognizer: UITapGestureRecognizer) {
        view.endEditing(true)
    }
    
    @objc func frpmDonePicked() {
        view.endEditing(true)
    }
    
    @objc func fromPeriodDateChanged(datePicker: UIDatePicker) {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "dd/MM/yyyy"
        let date = datePicker.date
        var dateComp = Calendar.current.dateComponents([.year, .month, .day, .hour, .minute, .second], from: date)
        dateComp.hour = 0
        dateComp.minute = 0
        dateComp.second = 0
        self.dateFrom = Calendar.current.date(from: dateComp) ?? date
        
        self.periodFromTExtField.text = dateFormatter.string(from: self.dateFrom)
    }
    
    @objc func toPeriodDateChanged(datePicker: UIDatePicker) {
       let dateFormatter = DateFormatter()
       dateFormatter.dateFormat = "dd/MM/yyyy"
        self.dateTo = datePicker.date
        self.periodToTextField.text = dateFormatter.string(from: self.dateTo)
    }
    
	public func updateChart() {
		sendRequest()
	}
    
	func millisecondsSince1970(date: Date, tzOffset: Int) -> Int64 {
		let milliseconds: Int64 = Int64((date.timeIntervalSince1970 * 1000.0).rounded())
		// add time zone offset
		return Int64(milliseconds + Int64(tzOffset * 3600000))
	}
    
	private func sendRequest() {
		let offset = TimeZone.current.secondsFromGMT() / 3600
		let postId = controller?._id
		let dateFrom = millisecondsSince1970(date: self.dateFrom, tzOffset: offset)
		let dateTo = millisecondsSince1970(date: self.dateTo, tzOffset: offset)
		let str = "/" + (postId ?? "") + "/packages/"
		let dateStr = String(dateFrom) + "/" + String(dateTo)
		let url = URL(string: Api.SERVER_URL + Api.CONTROLLER.URL_POSTS + str + dateStr)!
		let session = URLSession.shared;
		var request = URLRequest(url: url);

		request.setValue(self.token, forHTTPHeaderField: "Authorization")
		request.setValue("application/json", forHTTPHeaderField: "Content-Type");
		request.setValue("application/json", forHTTPHeaderField: "Accept");
		request.httpMethod = "GET";
		
		let task = session.dataTask(with: request as URLRequest, completionHandler: { data, response, error in
			
		guard let data = data,
            let response = response as? HTTPURLResponse, error == nil else {                                              // check for fundamental networking error
                 print("error", error ?? "Unknown error")
                 return
             }

             guard (200 ... 299) ~= response.statusCode else {                    // check for http errors
                 print("statusCode should be 2xx, but is \(response.statusCode)")
                 print("response = \(response)")
                 return
             }

             do {
                 let decoder = JSONDecoder()
                 let result = try decoder.decode(Array<PackageResponse>.self, from: data)
                 // successfull
                DispatchQueue.main.async {
                     self.updateChart(resultArray: result)
                }

             } catch let err {
                 print("\nErr", err)
                 return;
             }
		})
		task.resume();
	}

    func daysBetween(dateStart: Date, dateEnd: Date) -> Int {
        let calendar = Calendar.current
        let date1 = calendar.startOfDay(for: dateStart)
        let date2 = calendar.startOfDay(for: dateEnd)
        
        let components = calendar.dateComponents([.day], from: date1, to: date2)
        
        return components.day ?? 0
    }
    
    func updateChart(resultArray: Array<PackageResponse>) {
        // check current and previous resultArray
        // if they are equal, do nothing
        if (self.currentResultArray == resultArray) {
            return
        }
        // UPDATE POST CHART DATA
        // if not, save resultArray and update chart
        self.currentResultArray = resultArray
        self.barEntry.removeAll()

        var filterName = ""
        var units = ""
            
        if (self.selectedFilter == Constants.ChartFilter.chemistry_consumption ||
            self.selectedFilter == Constants.ChartFilter.electricity_consumption ||
            self.selectedFilter == Constants.ChartFilter.water_consumption) {
            filterName = Constants.PropNames.consumption
            units = Constants.PropNames.liter
        }
        else if (self.selectedFilter == Constants.ChartFilter.spent_money) {
            filterName = Constants.PropNames.sum
            units = Constants.PropNames.currency
        }
        else if (self.selectedFilter == Constants.ChartFilter.working_time) {
            filterName = Constants.PropNames.time
            units = ""
        }
            
        let dif = daysBetween(dateStart: self.dateFrom, dateEnd: self.dateTo)
        if (dif == 0) {
            updateHoursData(resultArray: resultArray, filterName: filterName, units: units)
        }
        else if (dif <= 31) {
            updateDaysData(resultArray: resultArray, filterName: filterName, units: units)
        }
        else if (dif > 31) {
            updateMonthsData(resultArray: resultArray, filterName: filterName, units: units)
        }
    }
    
    public func updateHoursData(resultArray: Array<PackageResponse>, filterName: String,
                                 units: String) {
        var maxValue = 0.0
        var result = 0.0
        let barSpace = 0.0
        let groupSpace = 0.1

        var mode1: [BarChartDataEntry] = []
        var mode2: [BarChartDataEntry] = []
        var mode3: [BarChartDataEntry] = []
        var mode4: [BarChartDataEntry] = []
        var mode5: [BarChartDataEntry] = []
        var mode6: [BarChartDataEntry] = []
        var mode7: [BarChartDataEntry] = []
        var mode8: [BarChartDataEntry] = []
        var mode9: [BarChartDataEntry] = []
        var mode10: [BarChartDataEntry] = []
        var mode11: [BarChartDataEntry] = []
        var mode12: [BarChartDataEntry] = []
        var mode13: [BarChartDataEntry] = []
        
        var mode1Value = 0.0, mode2Value = 0.0, mode3Value = 0.0, mode4Value = 0.0,
        mode5Value = 0.0, mode6Value = 0.0, mode7Value = 0.0, mode8Value = 0.0,
        mode9Value = 0.0, mode10Value = 0.0, mode11Value = 0.0, mode12Value = 0.0,
        mode13Value = 0.0
        
        for h in 0...(Constants.DAY_HOURS + 1) {
            for packageResponse in resultArray {
                let packageData = packageResponse.data
                let createdDate = packageResponse.getCreatedDate()
                
                let hours = Calendar.current.component(.hour, from: createdDate)
                if (h != hours) {
                    continue
                }
                
                // sup up all values for each mode
                let modes = packageData.modes
                for modeData in modes {
                // TODO: append swich filters
                switch (self.selectedFilter) {
                    case Constants.ChartFilter.chemistry_consumption: break
                    
                    case Constants.ChartFilter.electricity_consumption: break
                    
                    case Constants.ChartFilter.water_consumption: break
                    
                    case Constants.ChartFilter.spent_money:
                        // for case spend money
                        let value = modeData.getDoubleModeMoney()
                        if (value > maxValue) {
                            maxValue = Double(value)
                        }
                        
                        result += value
                        switch modeData.mode_id {
                            case Constants.Modes.MODE_1: mode1Value += value; break
                            case Constants.Modes.MODE_2: mode2Value += value; break
                            case Constants.Modes.MODE_3: mode3Value += value; break
                            case Constants.Modes.MODE_4: mode4Value += value; break
                            case Constants.Modes.MODE_5: mode5Value += value; break
                            case Constants.Modes.MODE_6: mode6Value += value; break
                            case Constants.Modes.MODE_7: mode7Value += value; break
                            case Constants.Modes.MODE_8: mode8Value += value; break
                            case Constants.Modes.MODE_9: mode9Value += value; break
                            case Constants.Modes.MODE_10: mode10Value += value; break
                            case Constants.Modes.MODE_11: mode11Value += value; break
                            case Constants.Modes.MODE_12: mode12Value += value; break
                            case Constants.Modes.MODE_13: mode13Value += value; break
                            default: break
                        }
                        break
                    
                    case Constants.ChartFilter.working_time:
                        break
                        
                    default: break
                    }
                }
            }
                    
            let pos = h
            mode1.append(BarChartDataEntry(x:Double(pos), y: mode1Value))
            mode2.append(BarChartDataEntry(x:Double(pos), y: mode2Value))
            mode3.append(BarChartDataEntry(x:Double(pos), y: mode3Value))
            mode4.append(BarChartDataEntry(x:Double(pos), y: mode4Value))
            mode5.append(BarChartDataEntry(x:Double(pos), y: mode5Value))
            mode6.append(BarChartDataEntry(x:Double(pos), y: mode6Value))
            mode7.append(BarChartDataEntry(x:Double(pos), y: mode7Value))
            mode8.append(BarChartDataEntry(x:Double(pos), y: mode8Value))
            mode9.append(BarChartDataEntry(x:Double(pos), y: mode9Value))
            mode10.append(BarChartDataEntry(x:Double(pos), y: mode10Value))
            mode11.append(BarChartDataEntry(x:Double(pos), y: mode11Value))
            mode12.append(BarChartDataEntry(x:Double(pos), y: mode12Value))
            mode13.append(BarChartDataEntry(x:Double(pos), y: mode13Value))
            
            mode1Value = 0.0
            mode2Value = 0.0
            mode3Value = 0.0
            mode4Value = 0.0
            mode5Value = 0.0
            mode6Value = 0.0
            mode7Value = 0.0
            mode8Value = 0.0
            mode9Value = 0.0
            mode10Value = 0.0
            mode11Value = 0.0
            mode12Value = 0.0
            mode13Value = 0.0
        }
       
        let set1 = BarChartDataSet(entries: mode1, label: Constants.ModeNames.water_presure)
        set1.setColor(Constants.Colors.water_presure)
        set1.valueFormatter = self.barValueFormatter
     
        let set2 = BarChartDataSet(entries: mode2, label: Constants.ModeNames.foam)
        set2.setColor(Constants.Colors.foam)
        set2.valueFormatter = self.barValueFormatter
        
        let set3 = BarChartDataSet(entries: mode3, label: Constants.ModeNames.vax)
        set3.setColor(Constants.Colors.vax)
        set3.valueFormatter = self.barValueFormatter
   
        let set4 = BarChartDataSet(entries: mode4, label: Constants.ModeNames.osmosis)
        set4.setColor(Constants.Colors.osmosis)
        set4.valueFormatter = self.barValueFormatter
    
        let set5 = BarChartDataSet(entries: mode5, label: Constants.ModeNames.warm_water)
        set5.setColor(Constants.Colors.warm_water)
        set5.valueFormatter = self.barValueFormatter
    
        let set6 = BarChartDataSet(entries: mode6, label: Constants.ModeNames.vacuum_cleaner)
        set6.setColor(Constants.Colors.vacuum_cleaner)
        set6.valueFormatter = self.barValueFormatter
       
        let set7 = BarChartDataSet(entries: mode7, label: Constants.ModeNames.hand_water)
        set7.setColor(Constants.Colors.hand_water)
        set7.valueFormatter = self.barValueFormatter
       
        let set8 = BarChartDataSet(entries: mode8, label: Constants.ModeNames.air)
        set8.setColor(Constants.Colors.air)
        set8.valueFormatter = self.barValueFormatter
       
        let set9 = BarChartDataSet(entries: mode9, label: Constants.ModeNames.tire)
        set9.setColor(Constants.Colors.tire)
        set9.valueFormatter = self.barValueFormatter
        
        let set10 = BarChartDataSet(entries: mode10, label: Constants.ModeNames.antimoshka)
        set10.setColor(Constants.Colors.antimoshka)
        set10.valueFormatter = self.barValueFormatter
       
        let set11 = BarChartDataSet(entries: mode11, label: Constants.ModeNames.disk_clean)
        set11.setColor(Constants.Colors.disk_clean)
        set11.valueFormatter = self.barValueFormatter
       
        let set12 = BarChartDataSet(entries: mode12, label: Constants.ModeNames.winter)
        set12.setColor(Constants.Colors.winter)
        set12.valueFormatter = self.barValueFormatter
       
        let set13 = BarChartDataSet(entries: mode13, label: Constants.ModeNames.carpet_clean)
        set13.setColor(Constants.Colors.carpet_clean)
        set13.valueFormatter = self.barValueFormatter
       
        self.barData = BarChartData(dataSets: [set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11, set12, set13])
        
        let xAxis = self.barChart!.xAxis
        xAxis.labelPosition = XAxis.LabelPosition.bottom        // place labels below X-axis
        xAxis.centerAxisLabelsEnabled = true
        
        let timeLabels = getTimeLabels();
        xAxis.valueFormatter = IndexAxisValueFormatter(values: timeLabels)
        xAxis.granularity = 1.0
        xAxis.granularityEnabled = true

        self.barData.barWidth = 0.1
        self.barChart.data = self.barData
        self.barChart.groupBars(fromX: 0, groupSpace: groupSpace, barSpace: barSpace);
        self.barChart.setVisibleXRangeMaximum(10);
        self.barChart.moveViewToX(0);
        self.barChart.notifyDataSetChanged()
        self.barChart.animate(xAxisDuration: 2.0, yAxisDuration: 2.0)
  
        var info = (self.controller?.title ?? "") + " "
        info += filterName + ": " + String(result) + " " + units
        self.resultTextField.text = info
    }

    private func updateDaysData(resultArray: [PackageResponse], filterName: String,
                                units: String) {
        let startValue = Calendar.current.component(.day, from: self.dateFrom)
        let dif = daysBetween(dateStart: self.dateFrom, dateEnd: self.dateTo)
        if (dif < 0) {
            return
        }
        
        var maxValue = 0.0
        var result = 0.0
        let barSpace = 0.0
        let groupSpace = 0.1

        var mode1: [BarChartDataEntry] = []
        var mode2: [BarChartDataEntry] = []
        var mode3: [BarChartDataEntry] = []
        var mode4: [BarChartDataEntry] = []
        var mode5: [BarChartDataEntry] = []
        var mode6: [BarChartDataEntry] = []
        var mode7: [BarChartDataEntry] = []
        var mode8: [BarChartDataEntry] = []
        var mode9: [BarChartDataEntry] = []
        var mode10: [BarChartDataEntry] = []
        var mode11: [BarChartDataEntry] = []
        var mode12: [BarChartDataEntry] = []
        var mode13: [BarChartDataEntry] = []
        
        var mode1Value = 0.0, mode2Value = 0.0, mode3Value = 0.0, mode4Value = 0.0,
        mode5Value = 0.0, mode6Value = 0.0, mode7Value = 0.0, mode8Value = 0.0,
        mode9Value = 0.0, mode10Value = 0.0, mode11Value = 0.0, mode12Value = 0.0,
        mode13Value = 0.0
        
        let currentDateComp = Calendar.current.dateComponents([.day, .month], from: self.dateFrom)
        let range = Calendar.current.range(of: .day, in: .month, for: self.dateFrom)
        let startNumDays = range?.count
        var currentDay = startValue
        var currentMonth = currentDateComp.month ?? 0
        
        for h in 0...(dif + 1) {
            
            for packageResponse in resultArray {
                let packageData = packageResponse.data
                let createdDate = packageResponse.getCreatedDate()

                let createdDateComp = Calendar.current.dateComponents([.day, .month], from: createdDate)

                if (createdDateComp.day != currentDay || createdDateComp.month != currentMonth) {
                    continue
                }
                
                // sup up all values for each mode
                let modes = packageData.modes
                for modeData in modes {
                    switch (self.selectedFilter) {
                    case Constants.ChartFilter.chemistry_consumption: break
                    
                    case Constants.ChartFilter.electricity_consumption: break
                    
                    case Constants.ChartFilter.water_consumption: break
                    
                    case Constants.ChartFilter.spent_money:
                    
                        // for case spend money
                        let value = modeData.getDoubleModeMoney()
                        if (value > maxValue) {
                            maxValue = Double(value)
                        }
                        
                        result += value
                        switch modeData.mode_id {
                        case Constants.Modes.MODE_1: mode1Value += value; break
                            case Constants.Modes.MODE_2: mode2Value += value; break
                            case Constants.Modes.MODE_3: mode3Value += value; break
                            case Constants.Modes.MODE_4: mode4Value += value; break
                            case Constants.Modes.MODE_5: mode5Value += value; break
                            case Constants.Modes.MODE_6: mode6Value += value; break
                            case Constants.Modes.MODE_7: mode7Value += value; break
                            case Constants.Modes.MODE_8: mode8Value += value; break
                            case Constants.Modes.MODE_9: mode9Value += value; break
                            case Constants.Modes.MODE_10: mode10Value += value; break
                            case Constants.Modes.MODE_11: mode11Value += value; break
                            case Constants.Modes.MODE_12: mode12Value += value; break
                            case Constants.Modes.MODE_13: mode13Value += value; break
                            default: break
                        }
                        break
                    
                    case Constants.ChartFilter.working_time: break;
                    default: break
                    }
                }
            }
            
            let pos = h
            mode1.append(BarChartDataEntry(x:Double(pos), y: mode1Value))
            mode2.append(BarChartDataEntry(x:Double(pos), y: mode2Value))
            mode3.append(BarChartDataEntry(x:Double(pos), y: mode3Value))
            mode4.append(BarChartDataEntry(x:Double(pos), y: mode4Value))
            mode5.append(BarChartDataEntry(x:Double(pos), y: mode5Value))
            mode6.append(BarChartDataEntry(x:Double(pos), y: mode6Value))
            mode7.append(BarChartDataEntry(x:Double(pos), y: mode7Value))
            mode8.append(BarChartDataEntry(x:Double(pos), y: mode8Value))
            mode9.append(BarChartDataEntry(x:Double(pos), y: mode9Value))
            mode10.append(BarChartDataEntry(x:Double(pos), y: mode10Value))
            mode11.append(BarChartDataEntry(x:Double(pos), y: mode11Value))
            mode12.append(BarChartDataEntry(x:Double(pos), y: mode12Value))
            mode13.append(BarChartDataEntry(x:Double(pos), y: mode13Value))
            
            mode1Value = 0.0
            mode2Value = 0.0
            mode3Value = 0.0
            mode4Value = 0.0
            mode5Value = 0.0
            mode6Value = 0.0
            mode7Value = 0.0
            mode8Value = 0.0
            mode9Value = 0.0
            mode10Value = 0.0
            mode11Value = 0.0
            mode12Value = 0.0
            mode13Value = 0.0
            
            // set nexе day in current comp
            if (currentDay == startNumDays) {
                // new month
                currentDay = 1
                currentMonth += 1
            }
            else {
                currentDay += 1
            }
        }
        
        let set1 = BarChartDataSet(entries: mode1, label: Constants.ModeNames.water_presure)
        set1.setColor(Constants.Colors.water_presure)
        set1.valueFormatter = self.barValueFormatter
     
        let set2 = BarChartDataSet(entries: mode2, label: Constants.ModeNames.foam)
        set2.setColor(Constants.Colors.foam)
        set2.valueFormatter = self.barValueFormatter
        
        let set3 = BarChartDataSet(entries: mode3, label: Constants.ModeNames.vax)
        set3.setColor(Constants.Colors.vax)
        set3.valueFormatter = self.barValueFormatter
   
        let set4 = BarChartDataSet(entries: mode4, label: Constants.ModeNames.osmosis)
        set4.setColor(Constants.Colors.osmosis)
        set4.valueFormatter = self.barValueFormatter
    
        let set5 = BarChartDataSet(entries: mode5, label: Constants.ModeNames.warm_water)
        set5.setColor(Constants.Colors.warm_water)
        set5.valueFormatter = self.barValueFormatter
    
        let set6 = BarChartDataSet(entries: mode6, label: Constants.ModeNames.vacuum_cleaner)
        set6.setColor(Constants.Colors.vacuum_cleaner)
        set6.valueFormatter = self.barValueFormatter
       
        let set7 = BarChartDataSet(entries: mode7, label: Constants.ModeNames.hand_water)
        set7.setColor(Constants.Colors.hand_water)
        set7.valueFormatter = self.barValueFormatter
       
        let set8 = BarChartDataSet(entries: mode8, label: Constants.ModeNames.air)
        set8.setColor(Constants.Colors.air)
        set8.valueFormatter = self.barValueFormatter
       
        let set9 = BarChartDataSet(entries: mode9, label: Constants.ModeNames.tire)
        set9.setColor(Constants.Colors.tire)
        set9.valueFormatter = self.barValueFormatter
        
        let set10 = BarChartDataSet(entries: mode10, label: Constants.ModeNames.antimoshka)
        set10.setColor(Constants.Colors.antimoshka)
        set10.valueFormatter = self.barValueFormatter
       
        let set11 = BarChartDataSet(entries: mode11, label: Constants.ModeNames.disk_clean)
        set11.setColor(Constants.Colors.disk_clean)
        set11.valueFormatter = self.barValueFormatter
       
        let set12 = BarChartDataSet(entries: mode12, label: Constants.ModeNames.winter)
        set12.setColor(Constants.Colors.winter)
        set12.valueFormatter = self.barValueFormatter
       
        let set13 = BarChartDataSet(entries: mode13, label: Constants.ModeNames.carpet_clean)
        set13.setColor(Constants.Colors.carpet_clean)
        set13.valueFormatter = self.barValueFormatter
       
        self.barData = BarChartData(dataSets: [set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11, set12, set13])
        
        let xAxis = self.barChart!.xAxis
        xAxis.centerAxisLabelsEnabled = true
        
        let timeLabels = getTimeLabels();
        xAxis.valueFormatter = IndexAxisValueFormatter(values: timeLabels)
        xAxis.granularity = 1.0
        xAxis.granularityEnabled = true

        self.barData.barWidth = 0.1
        self.barChart.data = self.barData
        self.barChart.groupBars(fromX: 0, groupSpace: groupSpace, barSpace: barSpace);
        self.barChart.setVisibleXRangeMaximum(15);
        self.barChart.moveViewToX(0);
        self.barChart.notifyDataSetChanged()
        self.barChart.animate(xAxisDuration: 2.0, yAxisDuration: 2.0)
  
        var info = (self.controller?.title ?? "") + " "
        info += filterName + ": " + String(result) + " " + units
        self.resultTextField.text = info
    }
    
    private func updateMonthsData(resultArray: [PackageResponse], filterName: String,
                                  units: String) {
        var maxValue = 0.0
        var result = 0.0
        
        let startValue = Calendar.current.component(.month, from: self.dateFrom)
        let endValue = Calendar.current.component(.month, from: self.dateTo)
        let dif = endValue - startValue
        let barSpace = 0.0
        let groupSpace = 0.1

        var mode1: [BarChartDataEntry] = []
        var mode2: [BarChartDataEntry] = []
        var mode3: [BarChartDataEntry] = []
        var mode4: [BarChartDataEntry] = []
        var mode5: [BarChartDataEntry] = []
        var mode6: [BarChartDataEntry] = []
        var mode7: [BarChartDataEntry] = []
        var mode8: [BarChartDataEntry] = []
        var mode9: [BarChartDataEntry] = []
        var mode10: [BarChartDataEntry] = []
        var mode11: [BarChartDataEntry] = []
        var mode12: [BarChartDataEntry] = []
        var mode13: [BarChartDataEntry] = []
        
        var mode1Value = 0.0, mode2Value = 0.0, mode3Value = 0.0, mode4Value = 0.0,
        mode5Value = 0.0, mode6Value = 0.0, mode7Value = 0.0, mode8Value = 0.0,
        mode9Value = 0.0, mode10Value = 0.0, mode11Value = 0.0, mode12Value = 0.0,
        mode13Value = 0.0
    
        var currentMonth = startValue
        
        for h in 0...(dif + 1) {
            for packageResponse in resultArray {
                let packageData = packageResponse.data
                let createdDate = packageResponse.getCreatedDate()

                let created = Calendar.current.component(.month, from: createdDate)
                if (currentMonth != created) {
                    continue
                }
                
                // sup up all values for each mode
                let modes = packageData.modes
                for modeData in modes {
                    switch (self.selectedFilter) {
                    case Constants.ChartFilter.chemistry_consumption: break
                    
                    case Constants.ChartFilter.electricity_consumption: break
                    
                    case Constants.ChartFilter.water_consumption: break
                    
                    case Constants.ChartFilter.spent_money:
                        // for case spend money
                        let value = modeData.getDoubleModeMoney()
                        if (value > maxValue) {
                            maxValue = Double(value)
                        }
                        
                        result += value
                        switch modeData.mode_id {
                            case Constants.Modes.MODE_1: mode1Value += value; break
                            case Constants.Modes.MODE_2: mode2Value += value; break
                            case Constants.Modes.MODE_3: mode3Value += value; break
                            case Constants.Modes.MODE_4: mode4Value += value; break
                            case Constants.Modes.MODE_5: mode5Value += value; break
                            case Constants.Modes.MODE_6: mode6Value += value; break
                            case Constants.Modes.MODE_7: mode7Value += value; break
                            case Constants.Modes.MODE_8: mode8Value += value; break
                            case Constants.Modes.MODE_9: mode9Value += value; break
                            case Constants.Modes.MODE_10: mode10Value += value; break
                            case Constants.Modes.MODE_11: mode11Value += value; break
                            case Constants.Modes.MODE_12: mode12Value += value; break
                            case Constants.Modes.MODE_13: mode13Value += value; break
                            default: break
                        }
                        break
                    
                    case Constants.ChartFilter.working_time: break
                    default: break
                    }
                }
            }
                
            let pos = h
            mode1.append(BarChartDataEntry(x:Double(pos), y: mode1Value))
            mode2.append(BarChartDataEntry(x:Double(pos), y: mode2Value))
            mode3.append(BarChartDataEntry(x:Double(pos), y: mode3Value))
            mode4.append(BarChartDataEntry(x:Double(pos), y: mode4Value))
            mode5.append(BarChartDataEntry(x:Double(pos), y: mode5Value))
            mode6.append(BarChartDataEntry(x:Double(pos), y: mode6Value))
            mode7.append(BarChartDataEntry(x:Double(pos), y: mode7Value))
            mode8.append(BarChartDataEntry(x:Double(pos), y: mode8Value))
            mode9.append(BarChartDataEntry(x:Double(pos), y: mode9Value))
            mode10.append(BarChartDataEntry(x:Double(pos), y: mode10Value))
            mode11.append(BarChartDataEntry(x:Double(pos), y: mode11Value))
            mode12.append(BarChartDataEntry(x:Double(pos), y: mode12Value))
            mode13.append(BarChartDataEntry(x:Double(pos), y: mode13Value))
        
            mode1Value = 0.0
            mode2Value = 0.0
            mode3Value = 0.0
            mode4Value = 0.0
            mode5Value = 0.0
            mode6Value = 0.0
            mode7Value = 0.0
            mode8Value = 0.0
            mode9Value = 0.0
            mode10Value = 0.0
            mode11Value = 0.0
            mode12Value = 0.0
            mode13Value = 0.0
            
            currentMonth += 1
        }
      
        let set1 = BarChartDataSet(entries: mode1, label: Constants.ModeNames.water_presure)
        set1.setColor(Constants.Colors.water_presure)
        set1.valueFormatter = self.barValueFormatter
     
        let set2 = BarChartDataSet(entries: mode2, label: Constants.ModeNames.foam)
        set2.setColor(Constants.Colors.foam)
        set2.valueFormatter = self.barValueFormatter
        
        let set3 = BarChartDataSet(entries: mode3, label: Constants.ModeNames.vax)
        set3.setColor(Constants.Colors.vax)
        set3.valueFormatter = self.barValueFormatter
   
        let set4 = BarChartDataSet(entries: mode4, label: Constants.ModeNames.osmosis)
        set4.setColor(Constants.Colors.osmosis)
        set4.valueFormatter = self.barValueFormatter
    
        let set5 = BarChartDataSet(entries: mode5, label: Constants.ModeNames.warm_water)
        set5.setColor(Constants.Colors.warm_water)
        set5.valueFormatter = self.barValueFormatter
    
        let set6 = BarChartDataSet(entries: mode6, label: Constants.ModeNames.vacuum_cleaner)
        set6.setColor(Constants.Colors.vacuum_cleaner)
        set6.valueFormatter = self.barValueFormatter
       
        let set7 = BarChartDataSet(entries: mode7, label: Constants.ModeNames.hand_water)
        set7.setColor(Constants.Colors.hand_water)
        set7.valueFormatter = self.barValueFormatter
       
        let set8 = BarChartDataSet(entries: mode8, label: Constants.ModeNames.air)
        set8.setColor(Constants.Colors.air)
        set8.valueFormatter = self.barValueFormatter
       
        let set9 = BarChartDataSet(entries: mode9, label: Constants.ModeNames.tire)
        set9.setColor(Constants.Colors.tire)
        set9.valueFormatter = self.barValueFormatter
        
        let set10 = BarChartDataSet(entries: mode10, label: Constants.ModeNames.antimoshka)
        set10.setColor(Constants.Colors.antimoshka)
        set10.valueFormatter = self.barValueFormatter
       
        let set11 = BarChartDataSet(entries: mode11, label: Constants.ModeNames.disk_clean)
        set11.setColor(Constants.Colors.disk_clean)
        set11.valueFormatter = self.barValueFormatter
       
        let set12 = BarChartDataSet(entries: mode12, label: Constants.ModeNames.winter)
        set12.setColor(Constants.Colors.winter)
        set12.valueFormatter = self.barValueFormatter
        
        let set13 = BarChartDataSet(entries: mode13, label: Constants.ModeNames.carpet_clean)
        set13.setColor(Constants.Colors.carpet_clean)
        set13.valueFormatter = self.barValueFormatter
       
        self.barData = BarChartData(dataSets: [set1, set2, set3, set4, set5, set6, set7, set8, set9, set10, set11, set12, set13])
        
        let xAxis = self.barChart!.xAxis
        xAxis.labelPosition = XAxis.LabelPosition.bottom        // place labels below
        xAxis.centerAxisLabelsEnabled = true
        
        let timeLabels = getTimeLabels();
        xAxis.valueFormatter = IndexAxisValueFormatter(values: timeLabels)
        xAxis.granularity = 1.0
        xAxis.granularityEnabled = true

        self.barData.barWidth = 0.1
        self.barChart.data = self.barData
        self.barChart.groupBars(fromX: 0, groupSpace: groupSpace, barSpace: barSpace);
        self.barChart.setVisibleXRangeMaximum(10);
        self.barChart.moveViewToX(0);
        self.barChart.notifyDataSetChanged()
        self.barChart.animate(xAxisDuration: 2.0, yAxisDuration: 2.0)
  
        var info = (self.controller?.title ?? "") + " "
        info += filterName + ": " + String(result) + " " + units
        self.resultTextField.text = info
    }

    func getTimeLabels() -> Array<String> {
        var labels: Array<String> = Array<String>()
        let dif = daysBetween(dateStart: self.dateFrom, dateEnd: self.dateTo)
        
        // period 1 day
        if (dif == 0) {
            let hourFrom = 0
            let hourTo = 23
            var hour = hourFrom
            
            while (hour != hourTo) {
                if (hourFrom > hourTo && hour > 24) {
                    hour = 0;
                }

                labels.append(String(hour))
                hour += 1;
            }
            
            labels.append(String(hour))
            return labels;
        }

        // period < day
        if (dif <= 31) {
            var comp = Calendar.current.dateComponents(in: TimeZone.current, from: self.dateFrom)
          
            let dayFrom = comp.day ?? 0
            comp = Calendar.current.dateComponents(in: TimeZone.current, from: self.dateTo)
            let dayTo = comp.day ?? 0
            var day = dayFrom
            
            if (day == dayTo) {
                labels.append(String(day))
                day += 1
            }
            
            while (day != dayTo) {
                if (dayFrom >= dayTo && day > 31) {
                    day = 1;
                }

                labels.append(String(day))
                day += 1
            }

            labels.append(String(day))
            
            return labels
        }

        // period > month
        if (dif > 31) {
            var comp = Calendar.current.dateComponents(in: TimeZone.current, from: self.dateFrom)
            let monthFrom = comp.month ?? 0
            comp = Calendar.current.dateComponents(in: TimeZone.current, from: self.dateTo)
            let monthTo = comp.month ?? 0

            // max period 1 year
            var month = monthFrom
            while (month != monthTo) {
                if (monthFrom > monthTo && month > 12) {
                    month = 0;
                }

                labels.append(String(month))
                month += 1
            }

            labels.append(String(month))
            print(labels)
            return labels
        }
        
        return labels;
    }
    
    func createModePickerView() {
        self.filterPicker = UIPickerView()
        self.filterPicker?.delegate = self
        self.filterTextView.inputView = self.filterPicker
    }
    
    func createPickerToolBar() {
        let toolBar = UIToolbar()
        toolBar.sizeToFit()
        
        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment: ""), style: .plain, target: self, action: #selector(PostChartViewController.dismissKeyboard))
        
        toolBar.setItems([spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true
        
        self.filterTextView.inputAccessoryView = toolBar
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
    }
}


extension PostChartViewController: UIPickerViewDelegate, UIPickerViewDataSource {
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return self.filters.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return self.filters[row]
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let filter = self.filters[row]
        self.selectedFilter = row
        self.filterTextView.text = filter
    }
}
