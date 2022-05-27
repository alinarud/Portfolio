//
//  CarTableViewController.swift
//  DeWash
//
//  Created by mac on 14.06.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

class CarTableViewController: UIViewController {
    @IBOutlet weak var carTableView: UITableView!
	var fields: Array<Fields>?
	var expensesData: ExpensesResponse?
	
    override func viewDidLoad() {
        super.viewDidLoad()

        self.carTableView.delegate = self
        self.carTableView.dataSource = self
        
        self.carTableView.layer.cornerRadius = 5
        self.carTableView.layer.borderWidth = 1
        self.carTableView.layer.borderColor = UIColor.gray.cgColor
    }
	
	public func setExpensesData(expensesData: ExpensesResponse?) {
		self.expensesData = expensesData
		self.fields = self.expensesData?.getOneCarFields()

		DispatchQueue.main.async {
            self.carTableView?.reloadData()
        }
	} 
	
	public func getExpensesData() -> ExpensesResponse? {
        return self.expensesData ?? nil
	}
}

extension CarTableViewController: CarExpensesCellDelegate {

    func titleChanged(fieldId: String, title: String) {
		let fields = self.expensesData?.getOneCarFields()
        for i in 0...(fields?.count ?? 0) {
            var field = self.fields?[i]
            if (field?.id == fieldId) {
                field?.title = title
				return
			}
		}
    }
    
    func valueChanged(fieldId: String, value: Double) {
        let fields = self.expensesData?.getOneCarFields()
        for i in 0...(fields?.count ?? 0) {
            var field = self.fields?[i]
			if (field?.id == fieldId) {
				field?.value = String(value)
				return
			}
		}
    }
    
    func unitsChanged(fieldId: String, units: String) {
        let fields = self.expensesData?.getOneCarFields()
        for i in 0...(fields?.count ?? 0) {
            var field = self.fields?[i]
			if (field?.id == fieldId) {
				field?.measure = units
				return
			}
		}
    }   
}

extension CarTableViewController: TotalExpensesTableDelegate {
    func dataChanged(data: ExpensesResponse?) {
        setExpensesData(expensesData: data)
    }
}

extension CarTableViewController: UITableViewDataSource, UITableViewDelegate {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.fields?.count ?? 0
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let field = self.fields?[indexPath.row]
        
        let cell = tableView.dequeueReusableCell(withIdentifier: "CarExpCell") as! CarExpensesTableViewCell
        
        cell.setData(field: field)
        cell.delegate = self
        return cell
    }
}
