//
//  ExpensesContainerViewController.swift
//  DeWash
//
//  Created by user on 04.03.2020.
//  Copyright © 2020 user. All rights reserved.
//

import Foundation
import UIKit

class ExpensesContainerViewController: UIViewController, TotalExpensesTableDelegate {
    func dataChanged(data: ExpensesResponse?) {
        print("data changed")
        
        self.expensesData = data
        
        // update data
        let keys = self.containerViewObjects.keys
        
        if (keys.contains(Constants.PropNames.expenses_car_table_segue)) {
            let carViewController: CarTableViewController = self.containerViewObjects[Constants.PropNames.expenses_car_table_segue] as! CarTableViewController
            carViewController.setExpensesData(expensesData: data)
        }
        
       if (keys.contains(Constants.PropNames.expenses_total_chart_segue)) {
            let chartViewController: TotalExpensesChartViewController = self.containerViewObjects[Constants.PropNames.expenses_total_chart_segue] as! TotalExpensesChartViewController
            chartViewController.updateExpensesFields(fields: self.expensesData?.getTotalFields() ?? nil)
        }
        
        if (keys.contains(Constants.PropNames.expenses_car_chart_segue)) {
            let carChartViewController: CarExpensesChartViewController = self.containerViewObjects[Constants.PropNames.expenses_car_chart_segue] as! CarExpensesChartViewController
            carChartViewController.updateExpensesFields(fields: self.expensesData?.getOneCarFields() ?? nil)
        }
    }
    

    fileprivate weak var viewController : UIViewController!
    fileprivate var containerViewObjects = Dictionary<String,UIViewController>()
	fileprivate var segueIdentifier : String!
	fileprivate var prevSegueIdentifier : String!
	
    var animationDurationWithOptions:(TimeInterval, UIView.AnimationOptions) = (0,[])
    
    //Identifier For First Container SubView
    @IBInspectable internal var firstLinkedSubView : String!
    
    var expensesData: ExpensesResponse?
	
    // Specifies which ever container view is on the front
    open var currentViewController : UIViewController{
        get {
            return self.viewController   
        }
    }
    
    public func getExpenses() -> ExpensesResponse? {
        return self.expensesData
    }
    
    public func setExpensesData(data: ExpensesResponse?) {
        self.expensesData = data
        
        // update data
        let keys = self.containerViewObjects.keys
        if (keys.contains(Constants.PropNames.expenses_total_table_segue)) {
            let tableViewController: TotalTableViewController = self.containerViewObjects[Constants.PropNames.expenses_total_table_segue] as! TotalTableViewController
            tableViewController.delegate = self
            tableViewController.setExpensesData(expensesData: data)
        }
        
        if (keys.contains(Constants.PropNames.expenses_car_table_segue)) {
            let carViewController: CarTableViewController = self.containerViewObjects[Constants.PropNames.expenses_car_table_segue] as! CarTableViewController
            carViewController.setExpensesData(expensesData: data)
        }
        
       if (keys.contains(Constants.PropNames.expenses_total_chart_segue)) {
            let chartViewController: TotalExpensesChartViewController = self.containerViewObjects[Constants.PropNames.expenses_total_chart_segue] as! TotalExpensesChartViewController
            chartViewController.updateExpensesFields(fields: self.expensesData?.getTotalFields() ?? nil)
        }
        
        if (keys.contains(Constants.PropNames.expenses_car_chart_segue)) {
            let carChartViewController: CarExpensesChartViewController = self.containerViewObjects[Constants.PropNames.expenses_car_chart_segue] as! CarExpensesChartViewController
            carChartViewController.updateExpensesFields(fields: self.expensesData?.getOneCarFields() ?? nil)
        }
    }
    
    override open func viewDidLoad() {
        super.viewDidLoad()
        
    }
    open override func viewDidAppear(_ animated: Bool) {
        if let identifier = firstLinkedSubView{
            segueIdentifierReceivedFromParent(identifier)
        }
    }
    override open func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    func segueIdentifierReceivedFromParent(_ identifier: String){
        print("segueIdentifierReceivedFromParent")
		// set previous identifier
		if (self.prevSegueIdentifier != identifier) {
			self.prevSegueIdentifier = self.segueIdentifier
			// update expensesData (sth could be changed)
			if (self.prevSegueIdentifier == Constants.PropNames.expenses_total_table_segue) {
				
                let prevViewController: TotalTableViewController = self.containerViewObjects[self.prevSegueIdentifier] as! TotalTableViewController
				self.expensesData = prevViewController.getExpensesData()
			}
            else if (self.prevSegueIdentifier == Constants.PropNames.expenses_car_table_segue) {
                
                let prevViewController: CarTableViewController = self.containerViewObjects[self.prevSegueIdentifier] as! CarTableViewController
                self.expensesData = prevViewController.getExpensesData()
            }
		}
		
        self.segueIdentifier = identifier
        self.performSegue(withIdentifier: self.segueIdentifier, sender: nil)  
    }
    
    override open func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if (segue.identifier == segueIdentifier) {
            //Remove Container View
            if (viewController != nil) {
                viewController.view.removeFromSuperview()
                viewController = nil
            }
            //Add to dictionary if isn't already there
            if ((self.containerViewObjects[self.segueIdentifier] == nil)){
                viewController = segue.destination
                self.containerViewObjects[self.segueIdentifier] = viewController
                
            }else{
                for (key, value) in self.containerViewObjects{
                    
                    if key == self.segueIdentifier{
                        viewController = value
                    }
                }
            }
            
            if (segue.identifier == Constants.PropNames.expenses_car_chart_segue) {
                let destVC = segue.destination as? CarExpensesChartViewController
                destVC?.setExpensesFields(fields: self.expensesData?.getOneCarFields() ?? nil)
            }
            else if (segue.identifier == Constants.PropNames.expenses_car_table_segue) {
                let destVC = segue.destination as? CarTableViewController
                destVC?.setExpensesData(expensesData: self.expensesData)
            }
            else if (segue.identifier == Constants.PropNames.expenses_total_chart_segue) {
                let destVC = segue.destination as? TotalExpensesChartViewController
                destVC?.setExpensesFields(fields: self.expensesData?.getTotalFields() ?? nil)
            }
            else if (segue.identifier == Constants.PropNames.expenses_total_table_segue) {
                let destVC = segue.destination as? TotalTableViewController
                destVC?.delegate = self
                destVC?.setExpensesData(expensesData: self.expensesData)
                
            }
            
            UIView.transition(with: self.view, duration: animationDurationWithOptions.0, options: animationDurationWithOptions.1, animations: {
                self.addChild(self.viewController)
                self.viewController.view.frame = CGRect(x: 0,y: 0, width: self.view.frame.width,height: self.view.frame.height)
                self.view.addSubview(self.viewController.view)
            }, completion: { (complete) in
                self.viewController.didMove(toParent: self)
            })
        }
    }
}
