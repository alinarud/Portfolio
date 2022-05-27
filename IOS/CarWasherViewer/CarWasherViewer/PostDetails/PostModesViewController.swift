//
//  PostModesViewController.swift
//  DeWash
//
//  Created by user on 02.04.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

class PostModesViewController: UIViewController, UITextFieldDelegate {

    var controller: Controller?
    var modePicker: UIPickerView?
    var token: String?
    var selectedModeIndex: Int = 0
    var modes: [Mode] = []
    
    @IBOutlet weak var selectModeTextField: UITextField!
    @IBOutlet weak var stateImageView: UIImageView!
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var descriptionTextField: UITextField!
    @IBOutlet weak var commentTextField: UITextField!
    @IBOutlet weak var serialNumberTextField: UITextField!
    @IBOutlet weak var spentMoneyTextField: UITextField!
    @IBOutlet weak var workingTimeTextField: UITextField!
    @IBOutlet weak var minuteCostTextField: UITextField!
    @IBOutlet weak var loanTimeTextField: UITextField!
    @IBOutlet weak var waterConsumptionTextField: UITextField!
    @IBOutlet weak var electricityConsupmptionTextField: UITextField!
    @IBOutlet weak var chemistryConsumptionTextField: UITextField!
    @IBOutlet weak var nameButton: UIButton!
    @IBOutlet weak var descriptionButton: UIButton!
    @IBOutlet weak var commentButton: UIButton!
    @IBOutlet weak var serialNumberButton: UIButton!
    @IBOutlet weak var chemistryConsumptionButton: UIButton!
    @IBOutlet weak var electricityConsumptionButton: UIButton!
    @IBOutlet weak var waterConsumptionButton: UIButton!
    @IBOutlet weak var loanTimeButton: UIButton!
    @IBOutlet weak var minuteCostButton: UIButton!
    @IBOutlet weak var workingTimeButton: UIButton!
    @IBOutlet weak var spentMoneyButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.nameTextField.delegate = self
        self.descriptionTextField.delegate = self
        self.commentTextField.delegate = self
        self.serialNumberTextField.delegate = self
        self.chemistryConsumptionTextField.delegate = self
        self.electricityConsupmptionTextField.delegate = self
        self.waterConsumptionTextField.delegate = self
        self.loanTimeTextField.delegate = self
        self.minuteCostTextField.delegate = self
        self.workingTimeTextField.delegate = self
        self.spentMoneyTextField.delegate = self
        
        // init modeNames
        self.modes = self.controller!.modes
       
        if (self.modes.count > 0) {
            createModePickerView()
            createPickerToolBar()
            initModeFields()
        }
    }
    
    public func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }
    
    @IBAction func chemistryConsumptionEditingChanged(_ sender: UITextField) {
        self.chemistryConsumptionButton.isEnabled = true
    }
    
    @IBAction func electricityConsumptionEditingChanged(_ sender: UITextField) {
        self.electricityConsumptionButton.isEnabled = true
    }
    
    @IBAction func waterConsumptionEditingChanged(_ sender: UITextField) {
        self.waterConsumptionButton.isEnabled = true
    }
    
    @IBAction func loanTimeEditingChanged(_ sender: UITextField) {
        self.loanTimeButton.isEnabled = true
    }
    
    @IBAction func minuteCostEditingChanged(_ sender: UITextField) {
        self.minuteCostButton.isEnabled = true
    }
    
    @IBAction func workingTimeEditingChanged(_ sender: UITextField) {
        self.workingTimeButton.isEnabled = true
    }
    
    @IBAction func spentMoneyEditingChanged(_ sender: UITextField) {
        self.spentMoneyButton.isEnabled = true
    }
    
    @IBAction func serialNumberEditingChanged(_ sender: UITextField) {
        self.serialNumberButton.isEnabled = true
    }
    
    @IBAction func nameEditingChanged(_ sender: UITextField) {
        self.nameButton.isEnabled = true
    }
    
    @IBAction func descriptionEditingChanged(_ sender: UITextField) {
        self.descriptionButton.isEnabled = true
    }
    
    @IBAction func commentEditingChanged(_ sender: UITextField) {
        self.commentButton.isEnabled = true
    }
    
    private func initModeFields() {
        let currentMode = self.modes[self.selectedModeIndex]
        
        let modeTitle = currentMode.title
        self.selectModeTextField.text = modeTitle
        
        if (currentMode.active == true) {
            self.stateImageView.image = UIImage(named: "green_circle")
        }
        else {
            self.stateImageView.image = UIImage(named: "red_circle")
        }

        self.nameTextField.text = modeTitle
        self.descriptionTextField.text = currentMode.description
        self.commentTextField.text = currentMode.comment
        self.spentMoneyTextField.text = String(currentMode.getSpentModey())
        self.serialNumberTextField.text = currentMode.id
        self.workingTimeTextField.text = String(currentMode.getWorkingTime())
        self.minuteCostTextField.text = String(currentMode.getMinuteCost())
        self.loanTimeTextField.text = String(currentMode.mode_pay_delay)
        self.waterConsumptionTextField.text = String(currentMode.mode_water)
        self.electricityConsupmptionTextField.text = String(currentMode.mode_energy)
        self.chemistryConsumptionTextField.text = String(currentMode.mode_chemical)
    }
    
    @IBAction func saveNameTapped(_ sender: UIButton) {
        self.nameTextField.resignFirstResponder()
       
        changeModeValue(key: Api.PARAMETERS.TITLE, value: self.nameTextField.text ?? "")
        self.nameButton.isEnabled = false
    }
    
    @IBAction func saveDescriptionTapped(_ sender: UIButton) {
        self.descriptionTextField.resignFirstResponder()
        
        changeModeValue(key: Api.PARAMETERS.DESCRIPTION, value: self.descriptionTextField.text ?? "")
        self.descriptionButton.isEnabled = false
    }
    
    @IBAction func saveCommentTapped(_ sender: UIButton) {
        self.commentTextField.resignFirstResponder()
        
        changeModeValue(key: Api.PARAMETERS.COMMENT, value: self.commentTextField.text ?? "")
        self.commentButton.isEnabled = false
    }
    
    @IBAction func saveSerialNumTapped(_ sender: UIButton) {
        self.serialNumberTextField.resignFirstResponder()
        self.serialNumberButton.isEnabled = false
        changeModeValue(key: Api.PARAMETERS.ID, value: self.serialNumberTextField.text ?? "")
    }
    
    @IBAction func saveSpentMoneyTapped(_ sender: UIButton) {
        self.spentMoneyTextField.resignFirstResponder()
        
        let value = Double(self.spentMoneyTextField.text!) ?? 0
        let spentMoney = Int(value * 100)
        changeModeValue(key: Api.PARAMETERS.MODE_MONEY, value: String(spentMoney))
        self.spentMoneyButton.isEnabled = false
    }
    
    @IBAction func saveWorkingTimeTapped(_ sender: UIButton) {
        self.workingTimeTextField.resignFirstResponder()
        
        let workingTime = self.workingTimeTextField.text ?? ""
        let arr = workingTime.components(separatedBy: ":")

        let hours = (Int(arr[0]) ?? 0) * 3600
        let minutes = (Int(arr[1]) ?? 0) * 60
        let secs = Int(arr[2]) ?? 0
        
        let result = hours + minutes + secs
        changeModeValue(key: Api.PARAMETERS.MODE_TIME, value: String(result))
        self.workingTimeButton.isEnabled = false
    }
    
    @IBAction func saveMinuteCostTapped(_ sender: UIButton) {
        self.minuteCostTextField.resignFirstResponder()
        
        let value = Double(self.minuteCostTextField.text!) ?? 0
        let cost = Int(value * 100)
        changeModeValue(key: Api.PARAMETERS.MODE_COST, value: String(cost))
        self.minuteCostButton.isEnabled = false
    }
    
    @IBAction func saveLoanTimeTapped(_ sender: UIButton) {
        self.loanTimeTextField.resignFirstResponder()
        
        changeModeValue(key: Api.PARAMETERS.MODE_PAY_DELAY, value: self.loanTimeTextField.text ?? "")
        self.loanTimeButton.isEnabled = false
    }
    
    @IBAction func saveWaterConsupmTapped(_ sender: UIButton) {
        self.waterConsumptionTextField.resignFirstResponder()
     
        changeModeValue(key: Api.PARAMETERS.MODE_WATER, value: self.waterConsumptionTextField.text ?? "")
        self.waterConsumptionButton.isEnabled = false
    }
    
    @IBAction func saveElectricityConsumpTapped(_ sender: UIButton) {
        self.electricityConsupmptionTextField.resignFirstResponder()
      
        changeModeValue(key: Api.PARAMETERS.MODE_ENERGY, value: self.electricityConsupmptionTextField.text ?? "")
        self.electricityConsumptionButton.isEnabled = false
    }
    
    @IBAction func saveChemistryConsumpTapped(_ sender: UIButton) {
        self.chemistryConsumptionTextField.resignFirstResponder()
        
        changeModeValue(key: Api.PARAMETERS.MODE_CHEMICAL, value: self.chemistryConsumptionTextField.text ?? "")
        self.chemistryConsumptionButton.isEnabled = false
    }
   
    private func changeModeValue(key: String, value: String) {
        let postId = controller?._id
        let currentMode = self.modes[self.selectedModeIndex]
        let modeId = currentMode._id
        let str = "/" + (postId ?? "") + "/" + (modeId )
        let url = URL(string: Api.SERVER_URL + Api.CONTROLLER.URL_CONTROLLER_MODE + str)!
        let session = URLSession.shared;
        var request = URLRequest(url: url);
        
        request.setValue(self.token, forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type");
        request.setValue("application/json", forHTTPHeaderField: "Accept");
        request.httpMethod = "PATCH";
        
        let json: [String: Any] = ["key" : key, "value" : value]
        let jsonData = try? JSONSerialization.data(withJSONObject: json)
        request.httpBody = jsonData
        
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
            let result = try decoder.decode(SetValueResponse.self, from: data)

            DispatchQueue.main.async {
                self.controller = result.controller
                self.modes = self.controller!.modes
                
                self.selectModeTextField.text = self.modes[self.selectedModeIndex].title
            }
                 
             } catch let err {
                 print("\nErr", err)
                 return;
             }
        })
        task.resume();
    }
    
    public func setController(controller: Controller?) {
        self.controller = controller
    }
    
    public func setToken(token: String?) {
        self.token = token
    }
                        
    func createModePickerView() {
        self.modePicker = UIPickerView()
        self.modePicker?.delegate = self
        self.selectModeTextField.inputView = self.modePicker
    }
    
    func createPickerToolBar() {
        let toolBar = UIToolbar()
        toolBar.sizeToFit()
        
        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment: ""), style: .plain, target: self, action: #selector(PostModesViewController.dismissKeyboard))
        
        toolBar.setItems([spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true
        
        self.selectModeTextField.inputAccessoryView = toolBar
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
    }
}

extension PostModesViewController: UIPickerViewDelegate, UIPickerViewDataSource {
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return self.modes.count
    }
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        let mode = self.modes[row]
        return mode.title
    }
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let mode = self.modes[row]
        self.selectedModeIndex = row
        self.selectModeTextField.text = mode.title
        initModeFields()
    }
}
