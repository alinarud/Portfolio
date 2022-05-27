//
//  PostInfoViewController.swift
//  DeWash
//
//  Created by user on 02.04.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

class PostInfoViewController: UIViewController, UITextFieldDelegate {

    var controller: Controller?
    var token: String?
    
    @IBOutlet weak var postStateImageView: UIImageView!
    @IBOutlet weak var softwareVersionLabel: UILabel!
    @IBOutlet weak var lastConnectionLabel: UILabel!
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var descriptionTextField: UITextField!
    @IBOutlet weak var serialNumberTextField: UITextField!
    @IBOutlet weak var freeModeTimeTextField: UITextField!
    @IBOutlet weak var pomp1TextField: UITextField!
    @IBOutlet weak var pomp2TextField: UITextField!
    @IBOutlet weak var totalCounterTextField: UITextField!
    @IBOutlet weak var putMoneyTextField: UITextField!
    @IBOutlet weak var discountMoneyTextField: UITextField!
    @IBOutlet weak var encashmentMoneyTextField: UITextField!
    @IBOutlet weak var commentTextField: UITextField!
    @IBOutlet weak var nameButton: UIButton!
    @IBOutlet weak var descriptionButton: UIButton!
    @IBOutlet weak var pump2Button: UIButton!
    @IBOutlet weak var freeModeTimeButton: UIButton!
    @IBOutlet weak var pump1Button: UIButton!
    @IBOutlet weak var serialNumberButton: UIButton!
    @IBOutlet weak var commentButton: UIButton!
    
    @IBAction func nameEditingChanged(_ sender: UITextField) {
        self.nameButton.isEnabled = true
    }
    
    @IBAction func descriptionEditingChanged(_ sender: UITextField) {
        self.descriptionButton.isEnabled = true
    }
    
    @IBAction func commentEditingChanged(_ sender: UITextField) {
        self.commentButton.isEnabled = true
    }
    
    @IBAction func serialNumberEditingChanged(_ sender: UITextField) {
        self.serialNumberButton.isEnabled = true
    }
    
    @IBAction func freeModeTimeEditingChanged(_ sender: UITextField) {
        self.freeModeTimeButton.isEnabled = true
    }
    
    @IBAction func pump2EditingChanged(_ sender: UITextField) {
        self.pump2Button.isEnabled = true
    }
    
    @IBAction func pump1EditingChanged(_ sender: UITextField) {
        self.pump1Button.isEnabled = true
    }
    
    public func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.nameTextField.delegate = self
        self.descriptionTextField.delegate = self
        self.serialNumberTextField.delegate = self
        self.freeModeTimeTextField.delegate = self
        self.pomp1TextField.delegate = self
        self.pomp2TextField.delegate = self
        self.totalCounterTextField.delegate = self
        self.putMoneyTextField.delegate = self
        self.discountMoneyTextField.delegate = self
        self.encashmentMoneyTextField.delegate = self
        self.commentTextField.delegate = self
        
        if (self.controller?.active == true) {
            self.postStateImageView.image = UIImage(named: "green_circle")
        }
        else {
            self.postStateImageView.image = UIImage(named: "red_circle")
        }
        
        self.softwareVersionLabel.text = (self.softwareVersionLabel.text ?? "") + " " +  (self.controller?.version ?? "")
        self.lastConnectionLabel.text = (self.lastConnectionLabel.text ?? "") + " " + (self.controller?.getLastConnectionDate() ?? "")
        
        self.nameTextField.text = self.controller?.title
        self.descriptionTextField.text = self.controller?.description
        self.serialNumberTextField.text = self.controller?.id
        
        let freeTime = self.controller?.free_usage_time
        self.freeModeTimeTextField.text = (freeTime ?? 0) <= 0 ? "" : String(freeTime ?? 0)
        
        let pump1Time = self.controller?.pump1_time
        self.pomp1TextField.text = (pump1Time ?? 0) <= 0 ? "" : String(pump1Time ?? 0)
        
        let pump2Time = self.controller?.pump2_time
        self.pomp2TextField.text = (pump2Time ?? 0) <= 0 ? "" : String(pump2Time ?? 0)
        
        let totalMoney = self.controller?.getTotalMoney()
        self.totalCounterTextField.text =  (totalMoney ?? 0.0) <= 0.0 ? "" : String(totalMoney ?? 0.0)

        self.putMoneyTextField.text = "" //(putMoney ?? 0.0) <= 0.0 ? "" : String(putMoney ?? 0.0)
        
        let discountMoney = self.controller?.getDiscountMoney()
        self.discountMoneyTextField.text = (discountMoney ?? 0.0) <= 0.0 ? "" : String(discountMoney ?? 0.0)
        
        let encashmentMoney = self.controller?.getEncashmentMoney()
        self.encashmentMoneyTextField.text = (encashmentMoney ?? 0.0) <= 0.0 ? "" : String(encashmentMoney ?? 0.0)
        
        self.commentTextField.text = self.controller?.comment
    }
    
    @IBAction func saveNameTapped(_ sender: Any) {
        self.nameTextField.resignFirstResponder()
        changeModeValue(key: Api.PARAMETERS.TITLE, value: self.nameTextField.text ?? "")
        self.nameButton.isEnabled = false
    }
    
    @IBAction func saveDescriptionTapped(_ sender: Any) {
        self.descriptionTextField.resignFirstResponder()
        changeModeValue(key: Api.PARAMETERS.DESCRIPTION, value: self.descriptionTextField.text ?? "")
        self.descriptionButton.isEnabled = false
    }
    
    @IBAction func savePomp1TimeTapped(_ sender: Any) {
        self.pomp1TextField.resignFirstResponder()
        changeModeValue(key: Api.PARAMETERS.PUMP1_TIME, value: self.pomp1TextField.text ?? "")
        self.pump1Button.isEnabled = false
    }
    
    @IBAction func saveCommentTapped(_ sender: UIButton) {
        self.commentTextField.resignFirstResponder()
        changeModeValue(key: Api.PARAMETERS.COMMENT, value: self.commentTextField.text ?? "")
        self.commentButton.isEnabled = false
    }
    
    @IBAction func savePomp2TimeTapped(_ sender: Any) {
        self.pomp2TextField.resignFirstResponder()
        changeModeValue(key: Api.PARAMETERS.PUMP2_TIME, value: self.pomp2TextField.text ?? "")
        self.pump2Button.isEnabled = false
    }
    
    @IBAction func saveSerialNumberTapped(_ sender: Any) {
        self.serialNumberTextField.resignFirstResponder()
        self.serialNumberButton.isEnabled = false
    }
    
    @IBAction func saveFreeModeTimeTapped(_ sender: UIButton) {
        self.freeModeTimeTextField.resignFirstResponder()
        changeModeValue(key: Api.PARAMETERS.FREE_USAGE_TIME, value: self.freeModeTimeTextField.text ?? "")
        self.freeModeTimeButton.isEnabled = false
    }
  
    private func changeModeValue(key: String, value: String) {
        let postId = controller?._id
        let str = "/" + (postId ?? "")
        let url = URL(string: Api.SERVER_URL + Api.CONTROLLER.URL_CONTROLLER_ID + str)!

        let session = URLSession.shared;
        var request = URLRequest(url: url);
        
        request.setValue(self.token, forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        request.setValue("application/json", forHTTPHeaderField: "Accept")
        request.httpMethod = "PATCH";

        let json: [String: Any] = ["key" : key, "value" : value]
        let jsonData = try? JSONSerialization.data(withJSONObject: json)
        request.httpBody = jsonData
               
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
    
    public func setController(controller: Controller?) {
        print("Post details setController")
        self.controller = controller
    }
    
    public func setToken(token: String?) {
        self.token = token
    }
}
