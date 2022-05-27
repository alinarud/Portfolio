//
//  TotalExpensesViewController.swift
//  DeWash
//
//  Created by user on 04.03.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit
import Charts

class TotalExpensesChartViewController: UIViewController {

    @IBOutlet weak var barChartView: BarChartView!
    var expensesData: Array<Fields>?
    var barEntry: [BarChartDataEntry] = [] // value's list for chart
    var barData: BarChartData = BarChartData()

    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    public func setExpensesFields(fields: Array<Fields>?) {
        self.expensesData = fields
    }
    
    public func updateExpensesFields(fields: Array<Fields>?) {
        setExpensesFields(fields: fields)
        updateData()
    }
    
    private func setXAxis() {
        let xAxis = self.barChartView!.xAxis
        xAxis.axisMinimum = 0
        xAxis.granularity = 1.0
        xAxis.granularityEnabled = true
        xAxis.centerAxisLabelsEnabled = true
        xAxis.labelPosition = XAxis.LabelPosition.bottom        // place labels below X-axis
        xAxis.drawLabelsEnabled = true
        xAxis.axisMaximum = 12
    }

    public func initExpensesChart() {
        let yAxis = self.barChartView!.leftAxis
        yAxis.labelCount = 30
        setXAxis();
        
        let barSpace = 0.02
        let groupSpace = 0.3
        let groupCount = 3.0

        self.barData.barWidth = 0.10
        let xAxis = self.barChartView!.xAxis
        xAxis.axisMinimum = 0
        
        let bChartData = self.barChartView!.barData
        let groupWidth = bChartData?.groupWidth(groupSpace: groupSpace, barSpace: barSpace)
        xAxis.axisMaximum = (groupWidth ?? 0) * groupCount
        
        self.barChartView.groupBars(fromX: 0, groupSpace: groupSpace, barSpace: barSpace)
    }

    public func updateData() {
        if ((self.expensesData?.count ?? 0) == 0) {
            return
        }
        
        var exp1: [BarChartDataEntry] = []
        var exp2: [BarChartDataEntry] = []
        var exp3: [BarChartDataEntry] = []
        var exp4: [BarChartDataEntry] = []
        var exp5: [BarChartDataEntry] = []
        var exp6: [BarChartDataEntry] = []
        var exp7: [BarChartDataEntry] = []
        
        var exp1Value = 0.0, exp2Value = 0.0, exp3Value = 0.0, exp4Value = 0.0,
            exp5Value = 0.0, exp6Value = 0.0, exp7Value = 0.0
        
        for i in 0...((self.expensesData?.count ?? 0) - 1) {
            let field = self.expensesData?[i]

            let id = (Int)(field?.id ?? "")
            switch id {
                case Constants.FieldsMainIds.MAIN_ID_RENT: exp1Value = field?.getDoubleValue() ?? 0.0; break
                case Constants.FieldsMainIds.MAIN_ID_WHATER_DRAIN_CONSUMPTION: exp2Value = field?.getDoubleValue() ?? 0.0; break
                case Constants.FieldsMainIds.MAIN_ID_ELECTRICITY_CALC: exp3Value = field?.getDoubleValue() ?? 0.0; break
                case Constants.FieldsMainIds.MAIN_ID_PROMOTIONS: exp4Value = field?.getDoubleValue() ?? 0.0; break
                case Constants.FieldsMainIds.MAIN_ID_SALARY: exp5Value = field?.getDoubleValue() ?? 0.0; break
                case Constants.FieldsMainIds.MAIN_ID_CHEMISTRY: exp6Value = field?.getDoubleValue() ?? 0.0; break
                case Constants.FieldsMainIds.MAIN_ID_ADD_EQUIPMENT: exp7Value = field?.getDoubleValue() ?? 0.0; break
                default: break
            }
        }
        
        exp1.append(BarChartDataEntry(x:Double(1), y: exp1Value))
        exp2.append(BarChartDataEntry(x:Double(2), y: exp2Value))
        exp3.append(BarChartDataEntry(x:Double(3), y: exp3Value))
        exp4.append(BarChartDataEntry(x:Double(4), y: exp4Value))
        exp5.append(BarChartDataEntry(x:Double(5), y: exp5Value))
        exp6.append(BarChartDataEntry(x:Double(6), y: exp6Value))
        exp7.append(BarChartDataEntry(x:Double(7), y: exp7Value))
        
        let set1 = BarChartDataSet(entries: exp1, label: Constants.ExpensesMoldFields.rent)
        set1.setColor(Constants.Colors.exp_color1)
        
        let set2 = BarChartDataSet(entries: exp2, label: Constants.ExpensesMoldFields.water_drain_consumption)
        set2.setColor(Constants.Colors.exp_color2)
        
        let set3 = BarChartDataSet(entries: exp3, label: Constants.ExpensesMoldFields.electricity_calculation)
        set3.setColor(Constants.Colors.exp_color3)
        
        let set4 = BarChartDataSet(entries: exp4, label: Constants.ExpensesMoldFields.promotions)
        set4.setColor(Constants.Colors.exp_color4)
        
        let set5 = BarChartDataSet(entries: exp5, label: Constants.ExpensesMoldFields.salary)
        set5.setColor(Constants.Colors.exp_color5)
        
        let set6 = BarChartDataSet(entries: exp6, label: Constants.ExpensesMoldFields.chemistry)
        set6.setColor(Constants.Colors.exp_color6)
        
        let set7 = BarChartDataSet(entries: exp7, label: Constants.ExpensesMoldFields.additional_equipment)
        set7.setColor(Constants.Colors.exp_color7)
        
        self.barData = BarChartData(dataSets: [set1, set2, set3, set4, set5, set6, set7])
        
        setXAxis();
       
        self.barChartView.data = self.barData
        self.barChartView.notifyDataSetChanged()

        self.barChartView.animate(xAxisDuration: 2.0, yAxisDuration: 2.0)
    }
}
