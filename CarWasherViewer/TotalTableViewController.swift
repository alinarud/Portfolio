//
//  TotalTableViewController.swift
//  DeWash
//
//  Created by mac on 14.06.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

protocol TotalExpensesTableDelegate {
    func dataChanged(data: ExpensesResponse?)
}

class TotalTableViewController: UIViewController {

    @IBOutlet weak var totalTableView: UITableView!
	var expensesData: ExpensesResponse?
	var fields: Array<Fields>?
    var delegate: TotalExpensesTableDelegate?
   
    override func viewDidLoad() {
        super.viewDidLoad()

        self.totalTableView.delegate = self
        self.totalTableView.dataSource = self
        
        self.totalTableView.layer.cornerRadius = 5
        self.totalTableView.layer.borderWidth = 1
        self.totalTableView.layer.borderColor = UIColor.gray.cgColor
    }
	
	public func setExpensesData(expensesData: ExpensesResponse?) {
		self.expensesData = expensesData

        self.fields = self.expensesData?.getTotalFields()
		DispatchQueue.main.async {
            self.totalTableView?.reloadData()
        }
	} 
	
	public func getExpensesData() -> ExpensesResponse? {
		return self.expensesData
	}
}

extension TotalTableViewController: TotalExpensesCellDelegate {

    func titleChanged(fieldId: String, title: String) {
		self.expensesData?.updateTotalExpensesFieldName(fieldId: fieldId, name: title)
		
        self.fields = self.expensesData?.getTotalFields()
		DispatchQueue.main.async {
            self.totalTableView.reloadData()
        }
    }
    
    func valueChanged(fieldId: String, value: String) {
        print("value changed")
		self.expensesData?.updateTotalExpensesFieldValue(fieldId: fieldId, value: value)
		
        self.fields = self.expensesData?.getTotalFields()
		DispatchQueue.main.async {
            self.totalTableView.reloadData()
        }
        
        self.delegate?.dataChanged(data: self.expensesData!)
    }
    
    func unitsChanged(fieldId: String, units: String) {
		let fields = self.expensesData?.getTotalFields()
        for i in 0...(fields?.count ?? 0) {
            var field = self.expensesData?.fields[i]
			if (field?.id == fieldId) {
				field?.measure = units
				return
			}
		}
    }   
}

extension TotalTableViewController: UITableViewDataSource, UITableViewDelegate {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.fields?.count ?? 0
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let field = self.fields?[indexPath.row]
        
        let cell = tableView.dequeueReusableCell(withIdentifier: "TotalExpCell") as! TotalExpensesTableViewCell
        
        cell.setData(field: field)
        cell.delegate = self
        return cell
    }
}
