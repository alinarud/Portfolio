//
//  PostAutomodesViewController.swift
//  DeWash
//
//  Created by user on 07.04.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

class PostAutomodesViewController: UIViewController, UITextFieldDelegate {
    
    var token: String?
    var controller: Controller?
    var modePicker: UIPickerView?
    var selectedModeIndex: Int = 0
    var automodes: [Automode] = []
    
    @IBOutlet weak var selectAutomodeTextField: UITextField!
    @IBOutlet weak var stateImageView: UIImageView!
    @IBOutlet weak var nameTextField: UITextField!
    @IBOutlet weak var descriptionTextField: UITextField!
    @IBOutlet weak var commentTextField: UITextField!
    @IBOutlet weak var serialNumberTextField: UITextField!
    @IBOutlet weak var workingTimeTextField: UITextField!
    @IBOutlet weak var turnOnTimeTextField: UITextField!
    @IBOutlet weak var descriptionButton: UIButton!
    @IBOutlet weak var commentButton: UIButton!
    @IBOutlet weak var nameButton: UIButton!
    @IBOutlet weak var serialNumberButton: UIButton!
    @IBOutlet weak var workingTimeButton: UIButton!
    @IBOutlet weak var turnOnTimeButton: UIButton!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.nameTextField.delegate = self
        self.descriptionTextField.delegate = self
        self.commentTextField.delegate = self
        self.serialNumberTextField.delegate = self
        self.workingTimeTextField.delegate = self
        self.turnOnTimeTextField.delegate = self
        
        // init modeNames
        self.automodes = self.controller!.automodes
   
        if (self.automodes.count > 0) {
            createModePickerView()
            createPickerToolBar()
            initAutomodeFields()
        }
    }
    
    public func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }
    
    @IBAction func serialNumberEditingChanged(_ sender: UITextField) {
        self.serialNumberButton.isEnabled = true
    }
    
    @IBAction func turnOnTimeEditingChanged(_ sender: UITextField) {
        self.turnOnTimeButton.isEnabled = true
    }
    
    @IBAction func workingTimeEditingChanged(_ sender: UITextField) {
        self.workingTimeButton.isEnabled = true
    }
    
    @IBAction func commentEditingChanged(_ sender: UITextField) {
        self.commentButton.isEnabled = true
    }
    
    @IBAction func descriptionEditingChanged(_ sender: UITextField) {
        self.descriptionButton.isEnabled = true
    }
    
    @IBAction func nameEditingChanged(_ sender: UITextField) {
        self.nameButton.isEnabled = true
    }
    
    private func initAutomodeFields() {
        let currentAutomode = self.automodes[self.selectedModeIndex]
        
        let autoModeTitle = currentAutomode.title
        self.selectAutomodeTextField.text = autoModeTitle
        
        if (currentAutomode.active == true) {
            self.stateImageView.image = UIImage(named: "green_circle")
        }
        else {
            self.stateImageView.image = UIImage(named: "red_circle")
        }

        self.nameTextField.text = currentAutomode.title
        self.descriptionTextField.text = currentAutomode.description
        self.commentTextField.text = currentAutomode.comment
        self.serialNumberTextField.text = currentAutomode.id
        self.workingTimeTextField.text = currentAutomode.getWorkingTime()
        self.turnOnTimeTextField.text = String(currentAutomode.auto_mode_delay)
    }
    
    func createModePickerView() {
        self.modePicker = UIPickerView()
        self.modePicker?.delegate = self
        self.selectAutomodeTextField.inputView = self.modePicker
    }
    
    func createPickerToolBar() {
        let toolBar = UIToolbar()
        toolBar.sizeToFit()
        
        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment: ""), style: .plain, target: self, action: #selector(PostAutomodesViewController.dismissKeyboard))
        
        toolBar.setItems([spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true
        
        self.selectAutomodeTextField.inputAccessoryView = toolBar
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
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
    
    @IBAction func saveSerialNumberTapped(_ sender: UIButton) {
        self.serialNumberTextField.resignFirstResponder()
        
        changeModeValue(key: Api.PARAMETERS.ID, value: self.serialNumberTextField.text ?? "")
        self.serialNumberButton.isEnabled = false
    }
    
    @IBAction func saveWorkingTimeTapped(_ sender: UIButton) {
        self.workingTimeTextField.resignFirstResponder()
        
        let workingTime = self.workingTimeTextField.text ?? ""
        let arr = workingTime.components(separatedBy: ":")

        let hours = (Int(arr[0]) ?? 0) * 3600
        let minutes = (Int(arr[1]) ?? 0) * 60
        let secs = Int(arr[2]) ?? 0
        
        let result = hours + minutes + secs
        
        changeModeValue(key: Api.PARAMETERS.AUTO_MODE_TIME, value: String(result))
        self.workingTimeButton.isEnabled = false
    }
    
    @IBAction func saveTurnonTimeTapped(_ sender: UIButton) {
        self.turnOnTimeTextField.resignFirstResponder()
        changeModeValue(key: Api.PARAMETERS.AUTO_MODE_DELAY, value: self.turnOnTimeTextField.text ?? "")
        self.turnOnTimeButton.isEnabled = false
    }
   
    private func changeModeValue(key: String, value: String) {
        let postId = controller?._id
        let currentMode = self.automodes[self.selectedModeIndex]
        let modeId = currentMode._id
        let str = "/" + (postId ?? "") + "/automodes/" + (modeId )
        let url = URL(string: Api.SERVER_URL + Api.CONTROLLER.URL_CONTROLLER_AUTOMODE + str)!
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
                    self.automodes = self.controller!.automodes
                    
                    self.selectAutomodeTextField.text = self.automodes[self.selectedModeIndex].title
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
}

extension PostAutomodesViewController: UIPickerViewDelegate, UIPickerViewDataSource {
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }

    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return self.automodes.count
    }

    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        let mode = self.automodes[row]
        return mode.title
    }

    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let mode = self.automodes[row]
        self.selectedModeIndex = row
        self.selectAutomodeTextField.text = mode.title
        initAutomodeFields()
    }
}
