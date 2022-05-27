//
//  ThrowableDecoder.swift
//  DeWash
//
//  Created by user on 11.03.2020.
//  Copyright © 2020 user. All rights reserved.
//

import Foundation

struct Throwable<T: Decodable>: Decodable {
    let result: Result<T, Error>
    
    init(from decoder: Decoder) throws {
        result = Result(catching: { try T(from: decoder)})
    }
}
