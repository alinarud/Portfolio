//
//  MainTabBarController.swift
//  DeWash
//
//  Created by user on 04.03.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

class MainTabBarController: UITabBarController, DeWashDataDelegate {
    
    private var updateTimer: Timer?
    var dewashData: DeWashDataStorage = DeWashDataStorage()
    
    func onTableValueChanged(expensesResponse: ExpensesResponse) {
        
    }
    
    func onLoginResponseReceived(loginResponse: LoginResponse) {
        
    }
    
    func onDataChanged(dewashData: DeWashDataStorage) {
        DispatchQueue.main.async {
            self.selectedIndex = 0
                 
            // for child in children {
            let viewController = self.children[0] as? ViewController
            viewController?.setDewashData(dewashData: self.dewashData)

            let expensesController = self.children[1] as? ExpensesViewController
            expensesController?.setDewashData(dewashData: self.dewashData)
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        self.navigationItem.setHidesBackButton(true, animated: true)
        self.navigationItem.rightBarButtonItem = UIBarButtonItem.init(title: NSLocalizedString("Exit", comment: ""), style: .done, target: self, action: #selector(self.actionExitClicked(sender:)))
       
        dewashData.delegate = self
    }
    
    @objc func actionExitClicked(sender: UIBarButtonItem) {
        // back to the login form
        self.navigationController?.popViewController(animated: true)
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        dewashData.initPosts()
        
        updateTimer = Timer.scheduledTimer(timeInterval: 30, target: self, selector: #selector(updateData), userInfo: nil, repeats: true)
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        updateTimer?.invalidate()
    }
    
    @objc
    func updateData() {
        // check what tab is active
        switch self.selectedIndex {
        case 0:
            dewashData.initPosts(); break
        case 1:
            // update expenses tab - do not do this
            break
        default:
            break
        }
    }
    
    override func didMove(toParent parent: UIViewController?) {
        super.didMove(toParent: parent)
    }
    
    public func setLoginResponse(loginResponse: LoginResponse?) {
        self.dewashData.loginResponse = loginResponse
    }
}
