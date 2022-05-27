//
//  TotalExpensesTableViewCell.swift
//  DeWash
//
//  Created by mac on 14.06.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

protocol TotalExpensesCellDelegate {
    func titleChanged(fieldId: String, title: String)
    func valueChanged(fieldId: String, value: String)
    func unitsChanged(fieldId: String, units: String)
}

class TotalExpensesTableViewCell: UITableViewCell, UITextFieldDelegate {
    
    @IBOutlet weak var titleTotalTextField: UITextField!
    @IBOutlet weak var valueTotalTextField: UITextField!
    @IBOutlet weak var unitsTotalTextField: UITextField!

    var fieldId: String?
    var delegate: TotalExpensesCellDelegate?
    
    override func awakeFromNib() {
        super.awakeFromNib()

        self.titleTotalTextField.delegate = self
        self.valueTotalTextField.delegate = self
        self.unitsTotalTextField.delegate = self
    }
    
    public func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }

    @IBAction func valueEditingEnded(_ sender: UITextField) {
        delegate?.valueChanged(fieldId: self.fieldId ?? "", value: valueTotalTextField.text ?? "")
    }
    
    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
    }
	
	func setData(field: Fields?) {
        self.fieldId = field?.id

        if (self.fieldId == String(0)) {
            self.titleTotalTextField.text = Constants.PropNames.title
            self.valueTotalTextField.text = Constants.PropNames.value
            self.unitsTotalTextField.text = Constants.PropNames.units
            
            self.titleTotalTextField.backgroundColor = Constants.Colors.light_blue
            self.valueTotalTextField.backgroundColor = Constants.Colors.light_blue
            self.unitsTotalTextField.backgroundColor = Constants.Colors.light_blue

        }
        else {
            self.titleTotalTextField.text = field?.title
            self.valueTotalTextField.text = field?.value
            self.unitsTotalTextField.text = field?.measure
            
            self.titleTotalTextField.backgroundColor = UIColor.white
            self.valueTotalTextField.backgroundColor = UIColor.white
            self.unitsTotalTextField.backgroundColor = UIColor.white
        }
    }
}
