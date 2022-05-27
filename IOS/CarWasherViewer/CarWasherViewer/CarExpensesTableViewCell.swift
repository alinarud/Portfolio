//
//  CarExpensesTableViewCell.swift
//  DeWash
//
//  Created by mac on 14.06.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit


protocol CarExpensesCellDelegate {
    func titleChanged(fieldId: String, title: String)
    func valueChanged(fieldId: String, value: Double)
    func unitsChanged(fieldId: String, units: String)
}

class CarExpensesTableViewCell: UITableViewCell, UITextFieldDelegate {

    @IBOutlet weak var titleCarTextField: UITextField!
    @IBOutlet weak var valueCarTextField: UITextField!
    @IBOutlet weak var unitsCarTextField: UITextField!

	var fieldId: String?
    var delegate: CarExpensesCellDelegate?

    override func awakeFromNib() {
        super.awakeFromNib()

        self.titleCarTextField.delegate = self
        self.valueCarTextField.delegate = self
        self.unitsCarTextField.delegate = self
    }
    
    public func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
    }
	
	func setData(field: Fields?) {
        print("set field data")
        self.fieldId = field?.id
		
        if (self.fieldId == String(0)) {
            self.titleCarTextField.text = Constants.PropNames.title
            self.valueCarTextField.text = Constants.PropNames.value
            self.unitsCarTextField.text = Constants.PropNames.units
            
            self.titleCarTextField.backgroundColor = Constants.Colors.light_blue
            self.valueCarTextField.backgroundColor = Constants.Colors.light_blue
            self.unitsCarTextField.backgroundColor = Constants.Colors.light_blue
        }
        else {
            self.titleCarTextField.text = field?.title
            self.valueCarTextField.text = field?.value
            self.unitsCarTextField.text = field?.measure
            
            self.titleCarTextField.backgroundColor = UIColor.white
            self.valueCarTextField.backgroundColor = UIColor.white
            self.unitsCarTextField.backgroundColor = UIColor.white
        }
    }
}
