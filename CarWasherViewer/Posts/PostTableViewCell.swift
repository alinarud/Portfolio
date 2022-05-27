//
//  PostTableViewCell.swift
//  DeWash
//
//  Created by user on 26.03.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

protocol PostCellDelegate {
    func didTapInfo(postId: String)
    func didTapModes(postId: String)
    func didTapChart(postId: String)
    func didTapAutomodes(postId: String)
}


class PostTableViewCell: UITableViewCell {

    @IBOutlet weak var postState: UIImageView!
    @IBOutlet weak var postName: UILabel!
    @IBOutlet weak var postId: UILabel!
    @IBOutlet weak var lastConnection: UILabel!
    @IBOutlet weak var putMoneyLabel: UILabel!
    @IBOutlet weak var encashmentMoney: UILabel!
    @IBOutlet weak var totalMoney: UILabel!
    
    var controllerId: String?
    var delegate: PostCellDelegate?
   
    override func awakeFromNib() {
        super.awakeFromNib()
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)
    }
    
    @IBAction func infoButtonTapped(_ sender: UIButton) {
        delegate?.didTapInfo(postId: self.controllerId ?? "")
    }
    
    @IBAction func modesButtonTapped(_ sender: UIButton) {
        delegate?.didTapModes(postId: self.controllerId ?? "")
    }
    
    @IBAction func chartButtonTapped(_ sender: UIButton) {
        delegate?.didTapChart(postId: controllerId ?? "")
    }
    
    @IBAction func automodesButtonTapped(_ sender: UIButton) {
        delegate?.didTapAutomodes(postId: controllerId ?? "")
        
    }
    
    func setPostData(controller: Controller) {
        print("set post data")
        self.controllerId = controller._id
        
        if (controller.active == true) {
            postState.image = UIImage(named: "green_circle")
        }
        else {
            postState.image = UIImage(named: "red_circle")
        }
        postName.text = controller.title
        postId.text = "ID: " + controller.id

        lastConnection.text = NSLocalizedString("Last connection: ", comment: "") + controller.getLastConnectionDate()
        putMoneyLabel.text = NSLocalizedString("Put money:", comment: "")
        encashmentMoney.text = NSLocalizedString("Encashment money: ", comment: "") + String(controller.getEncashmentMoney()) //String(controller.encashment_money)
        totalMoney.text = NSLocalizedString("Total money: ", comment: "") + String(controller.getTotalMoney()) //String(controller.total_money ?? 0)
    }
}
