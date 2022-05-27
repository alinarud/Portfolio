//
//  DewashDataDelegate.swift
//  DeWash
//
//  Created by user on 10.03.2020.
//  Copyright © 2020 user. All rights reserved.
//

import Foundation

protocol DeWashDataDelegate : AnyObject {
    func onLoginResponseReceived(loginResponse: LoginResponse)
    func onDataChanged(dewashData: DeWashDataStorage)
}
