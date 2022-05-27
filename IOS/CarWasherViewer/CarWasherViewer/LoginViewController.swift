//
//  LoginViewController.swift
//  DeWash
//
//  Created by user on 01.02.2020.
//  Copyright © 2020 user. All rights reserved.
//

import Foundation
import UIKit
import SwiftKeychainWrapper

class LoginViewController: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var userEmailTextField: UITextField!
    @IBOutlet weak var userPasswordTextField: UITextField!
    
    var isConnecting: Bool = false
    var loginResponse: LoginResponse?

    public func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true;
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.userEmailTextField.delegate = self
        self.userPasswordTextField.delegate = self
        
        // retriev password and login
        let retrievedPassword: String? = KeychainWrapper.standard.string(forKey: "userPassword")
        let retrievedLogin: String? = KeychainWrapper.standard.string(forKey: "userLogin")
        if (retrievedLogin == nil || retrievedPassword == nil) {
            return;
        }
        
        // set data to fields
        userEmailTextField.text = retrievedLogin
        userPasswordTextField.text = retrievedPassword
        
        // to login automatically
        connectToServer()
    }
    
    @IBAction func loginButtonTapped(_ sender: Any) {
        if (self.isConnecting == false) {
            connectToServer()
        }
    }

    func connectToServer() {
        let userLogin = userEmailTextField.text ?? "";
        let userPassword = userPasswordTextField.text ?? "";
        
        if ((userLogin.isEmpty) == true) {
            let msg = NSLocalizedString("User name is empty", comment: "")
            showMessage(strMessage: msg)
            return;
        }
        
        if ((userPassword.isEmpty) == true) {
            showMessage(strMessage: NSLocalizedString("Password is empty", comment: ""))
            return;
        }
        
        isConnecting = true
        let url = URL(string: "http://185.69.153.20:5000/api/login")!
        
        let parameters = ["email" : userLogin, "password" : userPassword];
        
        //create the session object
        let session = URLSession.shared

        //now create the URLRequest object using the url object
        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        
        do {
            request.httpBody = try JSONSerialization.data(withJSONObject: parameters, options: .prettyPrinted);
        } catch let error {
            print(error.localizedDescription);
        }
        
        request.setValue("application/json", forHTTPHeaderField: "Content-Type");
        request.setValue("application/json", forHTTPHeaderField: "Accept");
        
        let task = session.dataTask(with: request as URLRequest, completionHandler: { data, response, error in
            
            guard let data = data,
                let response = response as? HTTPURLResponse,
                error == nil else {                                              // check for fundamental networking error
                print("error", error ?? "Unknown error")
                self.isConnecting = false
                return
            }

            guard (200 ... 299) ~= response.statusCode else {                    // check for http errors
                print("statusCode should be 2xx, but is \(response.statusCode)")
                print("response = \(response)")
                
                DispatchQueue.main.async {
                    self.showMessage(statusCode: response.statusCode)
                    
                }
                self.isConnecting = false
                return
            }
            print(response)
            do {
                let decoder = JSONDecoder()
                self.loginResponse = try decoder.decode(LoginResponse.self, from: data)
                
            } catch let err {
                print("\nLoginViewController ERROR", err)
                self.isConnecting = false
                return;
            }
            
            // save login and password
            KeychainWrapper.standard.set(userPassword, forKey: "userPassword")
            KeychainWrapper.standard.set(userLogin, forKey: "userLogin")
            
            let def = UserDefaults.standard;
            def.set(true, forKey: "isUserLoggedIn");
            def.synchronize();
            
            DispatchQueue.main.async {
                self.isConnecting = false
                self.performSegue(withIdentifier: "MainTabBarSegue", sender: self)
            }
            
        })
        task.resume();
    }
    
    func showMessage(statusCode: Int) {
        if (statusCode != 400 || statusCode != 404) {
            return
        }
        
        var strError = ""
        switch statusCode {
            case 400: strError = NSLocalizedString("Wrong password", comment: "")
            case 404:
                strError = NSLocalizedString("User name not found", comment: "")
            default:
                let errorStr = HTTPURLResponse.localizedString(forStatusCode: statusCode)
                strError = NSLocalizedString(errorStr, comment : "")
        }
        
        let alert = UIAlertController(title: "Error", message: strError, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    
    func showMessage(strMessage: String) {
        let alert = UIAlertController(title: NSLocalizedString("Message", comment: ""), message: strMessage, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: NSLocalizedString("OK", comment: ""), style: .default, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        guard let tabView = segue.destination as? MainTabBarController else {return}
        tabView.setLoginResponse(loginResponse: self.loginResponse)
    }
}
