import UIKit
import MonthYearPicker

class ExpensesViewController: UIViewController {
    
    var container: ExpensesContainerViewController!
    var dewashData: DeWashDataStorage?
    var currentMonth: Int?
    var currentYear: Int?
    var expensesData: Array<ExpensesResponse>?
    
    @IBOutlet weak var segmentedControl: UISegmentedControl!
    @IBOutlet weak var monthTextField: UITextField!
  
    public func setDewashData(dewashData: DeWashDataStorage) {
        self.dewashData = dewashData
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        UILabel.appearance(whenContainedInInstancesOf: [UISegmentedControl.self]).numberOfLines = 0
        
        let dateComp = Calendar.current.dateComponents([.year, .month], from: Date())
        let defaults = UserDefaults.standard
        
        self.currentMonth = defaults.integer(forKey: Constants.defaultsKeys.expensesCurrentMonth)
        if (self.currentMonth ?? 0 <= 0) {
            self.currentMonth = dateComp.month
        }
        
        self.currentYear = defaults.integer(forKey: Constants.defaultsKeys.expensesCurrentYear)
        if (self.currentYear ?? 0 <= 0) {
            self.currentYear = dateComp.year
        }
        
        updateMonthTextField()
        updateExpenses()
        createMonthPickerView()
    }
    
    override func viewWillDisappear(_ animated: Bool) {
        let defaults = UserDefaults.standard
        defaults.set(self.currentMonth, forKey: Constants.defaultsKeys.expensesCurrentMonth)
        defaults.set(self.currentYear, forKey: Constants.defaultsKeys.expensesCurrentYear)
    }
    
    @IBAction func updateExpensesClicked(_ sender: Any) {
        // reinit expenses array (send request to server)
        updateExpenses()
    }
    
    @IBAction func saveExpensesClicked(_ sender: Any) {
        // save all data
        //get data from car table and total table
        let expenses = self.container!.getExpenses()
        saveExpensesData(expensesResponse: expenses)
    }
    
    private func updateMonthTextField() {
        let txt = NSLocalizedString("Period for ", comment:"") + String(self.currentMonth ?? 0) + NSLocalizedString(" month ", comment:"")
            + String(self.currentYear ?? 0) + NSLocalizedString(" year", comment:"")
        self.monthTextField.text = txt
    }
    
    func createMonthPickerView() {
        let picker = MonthYearPickerView(frame: CGRect(origin: CGPoint(x: 0, y: (view.bounds.height - 216) / 2), size: CGSize(width: view.bounds.width, height: 216)))
        let calendar = Calendar.current

        var dateComponents: DateComponents? = calendar.dateComponents([.month, .year], from: Date())
        dateComponents?.month = self.currentMonth
        dateComponents?.year = self.currentYear

        let date: Date? = calendar.date(from: dateComponents!)
        picker.date = date ?? Date()
        
        picker.addTarget(self, action: #selector(dateChanged(datePicker:)), for: .valueChanged)

        let toolBar = UIToolbar(frame: CGRect(x: 0, y: 0, width: view.bounds.width, height: 35))
        toolBar.barStyle = UIBarStyle.default
        toolBar.isTranslucent = true
        toolBar.sizeToFit()

        let cancelButton = UIBarButtonItem(title: NSLocalizedString("Cancel", comment:""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.cancelPicked))
        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment:""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.donePicked))

        toolBar.setItems([cancelButton, spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true

        self.monthTextField.inputView = picker
        self.monthTextField.inputAccessoryView = toolBar
    }
    
    @objc func cancelPicked() {
        view.endEditing(true)
    }
    
    @objc func donePicked() {
        view.endEditing(true)
    
        updateMonthTextField()
        
        if (self.expensesData?.count == 0) {
            updateExpenses()
            return
        }
        
        let exp = self.expensesData?[0]
        if (self.currentYear != exp?.year) {
            updateExpenses()
            return
        }

        // set expenses data for new month for views
        if ((self.expensesData?.count ?? 0) == 0) {
            return;
        }
        for i in 0...((self.expensesData?.count ?? 0) - 1) {
            let val = self.expensesData?[i]
            if (val?.month == self.currentMonth) {
                self.container!.setExpensesData(data: val)
            }
        }
    }
    
    @objc func dateChanged(datePicker: MonthYearPickerView) {
 
        let dateComp = Calendar.current.dateComponents([.year, .month], from: datePicker.date)
        self.currentMonth = dateComp.month
        self.currentYear = dateComp.year
    }
    
    func createPickerToolBar() {
        let toolBar = UIToolbar()
        toolBar.sizeToFit()
        
        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment:""), style: .plain, target: self, action: #selector(ExpensesViewController.dismissKeyboard))
        
        toolBar.setItems([spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true
        
        self.monthTextField.inputAccessoryView = toolBar
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
    }
   
    override func didReceiveMemoryWarning() {
       super.didReceiveMemoryWarning()
    }
       
    @IBAction func segmentControl(_ sender: UISegmentedControl) {
        if (sender.selectedSegmentIndex == 0) {
            container!.segueIdentifierReceivedFromParent(Constants.PropNames.expenses_total_chart_segue)
        }
        else if (sender.selectedSegmentIndex == 1) {
            container!.segueIdentifierReceivedFromParent(Constants.PropNames.expenses_total_table_segue)
        }
        else if (sender.selectedSegmentIndex == 2) {
            container!.segueIdentifierReceivedFromParent(Constants.PropNames.expenses_car_chart_segue)
        }
        else if (sender.selectedSegmentIndex == 3) {
            container!.segueIdentifierReceivedFromParent(Constants.PropNames.expenses_car_table_segue)
        }
    }
       
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
       if segue.identifier == "container" {
            container = segue.destination as? ExpensesContainerViewController
            container?.animationDurationWithOptions = (0.2, .transitionFlipFromBottom)
       }
    }
   
    private func updateExpenses() {
        let str = "/" + String(self.currentYear ?? 0) //+ "/" + String(self.currentMonth ?? 0)
        let url = URL(string: Api.SERVER_URL + Api.EXPENSES.URL_EXPENSES + str)!
        let session = URLSession.shared;
        var request = URLRequest(url: url);
        let token = self.dewashData?.getToken()
        
        request.setValue(token, forHTTPHeaderField: "Authorization")
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
                let result = try decoder.decode(Array<ExpensesResponse>.self, from: data)

                self.expensesData = result
                for i in 0...((self.expensesData?.count ?? 0) - 1) {
                    let val = self.expensesData?[i]
                    if (val?.month == self.currentMonth) {
                        self.container!.setExpensesData(data: val)
                    }
                }
            } catch let err {
             print("\nError: ", err)
             return;
            }
        })
        task.resume();
    }
    
    public func saveExpensesData(expensesResponse: ExpensesResponse?) {
        let url = URL(string: Api.SERVER_URL + Api.EXPENSES.URL_EXPENSES)!
        let session = URLSession.shared;
        var request = URLRequest(url: url);
        let token = self.dewashData?.getToken()
        
        var expRequest: ExpensesRequest! = ExpensesRequest(year: 0, month: 0, expenses: [Fields]())
        expRequest.year = self.currentYear ?? 0
        expRequest.month = self.currentMonth ?? 0
        expRequest.expenses = expensesResponse?.fields ?? [Fields]()
        
        request.setValue(token, forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type");
        request.setValue("application/json", forHTTPHeaderField: "Accept");
        request.httpMethod = "POST";
        
        let encoder = JSONEncoder()
        do {
            let jsonData = try encoder.encode(expRequest)
                        request.httpBody = jsonData
            print("jsonData: ", String(data: request.httpBody!, encoding: .utf8) ?? "no body data")
        } catch {
            print(String(describing: error))
        }
        
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
                 let _ = try decoder.decode(ExpensesResponse.self, from: data)
             } catch let err {
                 print("\nError: ", err)
                 return;
             }
        })
        task.resume();
    }
}

extension ExpensesViewController: TotalExpensesTableDelegate {
    func dataChanged(data: ExpensesResponse?) {
     
    }
}
