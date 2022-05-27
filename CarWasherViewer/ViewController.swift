//
//  ViewController.swift
//  DeWash
//
//  Created by user on 11.01.2020.
//  Copyright © 2020 user. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var detailedInfoLabel: UILabel!
    @IBOutlet weak var periodFromTextField: UITextField!
    @IBOutlet weak var periodToTextField: UITextField!
    @IBOutlet weak var postsTableView: UITableView!
    
    var dewashData: DeWashDataStorage?
    var isLogged: Bool = false
    var selectedPostId: String = ""
    var posts: Array<Controller> = []
    
    private var fromPeriodDatePicker: UIDatePicker?
    private var toPeriodDatePicker: UIDatePicker?
    private var dateFrom: Date = Date()
    private var dateTo: Date = Date()
    
    @IBAction func periodFromEditingBegan(_ sender: Any) {
        if (self.periodFromTextField.text!.isEmpty) {
            let dateFormat = DateFormatter()
            dateFormat.dateFormat = "dd/MM/yyyy"
            self.periodFromTextField.text = dateFormat.string(from: Date())
        }
    }
    
    @IBAction func periodFromEditingEnded(_ sender: Any) {
    }
    
    @IBAction func periodToEditingBegan(_ sender: Any) {
        if (self.periodToTextField.text!.isEmpty) {
            let dateFormat = DateFormatter()
            dateFormat.dateFormat = "dd/MM/yyyy"
            self.periodToTextField.text = dateFormat.string(from: Date())
        }
    }
    
    @IBAction func periodToEditingEnded(_ sender: Any) {
        // check if to bigger than from
        // update posts info
        updatePeriodData()
    }
  
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.navigationItem.setHidesBackButton(true, animated: true)
        
        let systemFontAttributes = [NSAttributedString.Key.font: UIFont.systemFont(ofSize: 17.0)]
        UITabBarItem.appearance().setTitleTextAttributes(systemFontAttributes, for: .normal)
                
        self.postsTableView.delegate = self
        self.postsTableView.dataSource = self
        self.postsTableView.layer.cornerRadius = 5
        self.postsTableView.layer.borderWidth = 1
        self.postsTableView.layer.borderColor = UIColor.gray.cgColor
        self.postsTableView.backgroundView = UIImageView(image: UIImage(named: "drops_long"))
        
        initDateToPicker()
        initDateFromPicker()
        
        let dateFormat = DateFormatter()
        dateFormat.dateFormat = "dd/MM/yyyy"
        
        var dateComp = Calendar.current.dateComponents([.year, .month, .day, .hour, .minute, .second], from: self.dateFrom)
        dateComp.hour = 0
        dateComp.minute = 0
        dateComp.second = 0
        
        self.dateFrom = Calendar.current.date(from: dateComp) ?? Date()
        self.periodFromTextField.text = dateFormat.string(from: self.dateFrom)
        self.periodToTextField.text = dateFormat.string(from: self.dateTo)
        self.isLogged = false
    }
    
    private func initDateFromPicker() {
        self.fromPeriodDatePicker = UIDatePicker()
        
        if #available(iOS 13.4, *) {
            self.fromPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.fromPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.fromPeriodDatePicker?.preferredDatePickerStyle = .wheels
            self.fromPeriodDatePicker?.preferredDatePickerStyle = .wheels
        }
        
        self.fromPeriodDatePicker?.datePickerMode = .date
        self.fromPeriodDatePicker?.addTarget(self, action: #selector(ViewController.fromPeriodDateChanged(datePicker:)), for: .valueChanged)

        let toolBar = UIToolbar(frame: CGRect(origin: .zero, size: CGSize(width: 100, height: 44.0)))
        toolBar.barStyle = UIBarStyle.default
        toolBar.isTranslucent = true
        toolBar.sizeToFit()

        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.fromDonePicked))
        let cancelButton = UIBarButtonItem(title: NSLocalizedString("Cancel", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.cancelPicked))

        toolBar.setItems([cancelButton, spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true

        self.periodFromTextField.inputView = self.fromPeriodDatePicker
        self.periodFromTextField.inputAccessoryView = toolBar
    }
    
    private func initDateToPicker() {
        self.toPeriodDatePicker = UIDatePicker()
        
        if #available(iOS 13.4, *) {
            self.toPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.toPeriodDatePicker?.frame = CGRect(x: 0, y: 0, width: self.view.bounds.width, height: 250.0)
            self.toPeriodDatePicker?.preferredDatePickerStyle = .wheels
            self.toPeriodDatePicker?.preferredDatePickerStyle = .wheels
        }
        
       self.toPeriodDatePicker?.datePickerMode = .date
       self.toPeriodDatePicker?.addTarget(self, action: #selector(PostChartViewController.toPeriodDateChanged(datePicker:)), for: .valueChanged)
           
        let toolBar = UIToolbar(frame: CGRect(origin: .zero, size: CGSize(width: 100, height: 44.0)))
        toolBar.barStyle = UIBarStyle.default
        toolBar.isTranslucent = true
        toolBar.sizeToFit()

        let spaceButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonItem.SystemItem.flexibleSpace, target: nil, action: nil)
        let doneButton = UIBarButtonItem(title: NSLocalizedString("Done", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.fromDonePicked))

        let cancelButton = UIBarButtonItem(title: NSLocalizedString("Cancel", comment: ""), style: UIBarButtonItem.Style.done, target: self, action: #selector(self.cancelPicked))
        
        toolBar.setItems([cancelButton, spaceButton, doneButton], animated: false)
        toolBar.isUserInteractionEnabled = true

        self.periodToTextField.inputView = self.toPeriodDatePicker
        self.periodToTextField.inputAccessoryView = toolBar
    }
    
    
    @objc func fromDonePicked() {
        view.endEditing(true)
        updatePeriodData()
    }
    
    @objc func cancelPicked() {
        view.endEditing(true)
    }
    
    @objc func viewTapped(gestureRecognizer: UITapGestureRecognizer) {
        view.endEditing(true)
    }
    
    @objc func fromPeriodDateChanged(datePicker: UIDatePicker) {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "dd/MM/yyyy"
        self.dateFrom = datePicker.date
        self.periodFromTextField.text = dateFormatter.string(from: self.dateFrom)
    }
    
    @objc func toPeriodDateChanged(datePicker: UIDatePicker) {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "dd/MM/yyyy"
        self.dateTo = datePicker.date
        self.periodToTextField.text = dateFormatter.string(from: self.dateTo)
    }
    
    public func setDewashData(dewashData: DeWashDataStorage) {
        self.dewashData = dewashData
        self.posts = dewashData.getPosts()
       
        // update table
        DispatchQueue.main.async {
            self.postsTableView.reloadData()
        }
        
        setDetailedPostsInfo()
    }
    
    override func viewDidAppear(_ animated: Bool) {
     
    }
    
    private func setDetailedPostsInfo() {
        var totalEncashment = 0.0
        var totalMoney = 0.0
        
        for controller in self.posts {
            totalEncashment += controller.getEncashmentMoney()
            totalMoney += controller.getTotalMoney()
        }
        
        // set data       
        DispatchQueue.main.async {
            let info = NSLocalizedString("Total posts calculation: \nPut money: 0.0\nEncashment money: ", comment: "") + String(totalEncashment)
					+ NSLocalizedString("\nTotal money: ", comment: "") + String(totalMoney)
            self.detailedInfoLabel.text = info
        }
    }
    
    private func updatePeriodData() {
        if (self.dateTo < self.dateFrom) {
            return
        }
        
        getPostsValuesByPeriod()
    }

    func getPostsValuesByPeriod() {
        var urlComponents = URLComponents(string: Api.SERVER_URL + Api.CONTROLLER.URL_VALUE_BY_PERIOD)!
        
        let token = self.dewashData?.getToken()
        let ids = getPostsIds()
        let dateFrom = self.dateFrom.timeIntervalSince1970
        let dateTo = self.dateTo.timeIntervalSince1970
        
        urlComponents.queryItems = [
            URLQueryItem(name: "ids", value: ids),
            URLQueryItem(name: "from", value: String(dateFrom)),
            URLQueryItem(name: "to", value: String(dateTo))
        ]
        
        guard let url = urlComponents.url else {
            print("cannpt convert url from urlComponents")
            return
        }
        
        let session = URLSession.shared;
        var request = URLRequest(url: url);
        
        request.setValue(token, forHTTPHeaderField: "Authorization")
        request.setValue("application/json", forHTTPHeaderField: "Content-Type");
        request.setValue("application/json", forHTTPHeaderField: "Accept");
        request.httpMethod = "GET";
        
        let task = session.dataTask(with: request as URLRequest, completionHandler: { data, response, error in
            
            // set posts into posts variable
            guard let data = data,
                let response = response as? HTTPURLResponse,
                error == nil else {                                              // check for fundamental networking error
                print("error", error ?? "Unknown error")
                return
            }

            guard (200 ... 299) ~= response.statusCode else {                    // check for http errors
                print("statusCode should be 2xx, but is \(response.statusCode)")
                print("response = \(response)")
                
                do {
                    let decoder = JSONDecoder()
                    let errorResponse = try decoder.decode(ErrorResponse.self, from: data)
                    print("Status: \(errorResponse.status)")
                    print("Message: \(errorResponse.message)")
                }
                catch let err {
                    print("\nErr", err)
                    return;
                }
                return
            }
           
            do {
                let decoder = JSONDecoder()
                let response = try decoder.decode(Array<ValuesByPeriodResponse>.self, from: data)
                self.setPeriodPostsData(periodData: response)
                
            } catch let err {
                print("\nErr", err)
                return;
            }
        })
        task.resume();
    }
    
    private func getPostsIds() -> String {
        var array = [String]()
        for controller in self.posts {
            array.append(controller._id)
        }
        
        return array.joined(separator: ",")
    }
    
    private func setPeriodPostsData(periodData: Array<ValuesByPeriodResponse>) {
        var putMoney = 0.0
        
        var array = [String]()
        for postData in periodData {
            let totalValue = postData.getDoubleTotalValue()
            
            array.append(postData._id + ": " + String(totalValue))
            putMoney += totalValue
        }
        
        DispatchQueue.main.async {
            self.detailedInfoLabel.text = NSLocalizedString("Put money: ", comment: "") + String(putMoney) + "\n" + array.joined(separator: "\n")
        }
    }
    
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if (segue.identifier == Constants.PropNames.post_info_segue) {
            let destVC = segue.destination as? PostInfoViewController
            let controller = getController(postId: self.selectedPostId)
            destVC?.setController(controller: controller)
            destVC?.setToken(token: self.dewashData?.getToken())
        }
        else if (segue.identifier == Constants.PropNames.post_modes_segue) {
            let destVC = segue.destination as? PostModesViewController
            let controller = getController(postId: self.selectedPostId)
            destVC?.setController(controller: controller)
            destVC?.setToken(token: self.dewashData?.getToken())
        }
        else if (segue.identifier == Constants.PropNames.post_chart_segue) {
            let destVC = segue.destination as? PostChartViewController
            let controller = getController(postId: self.selectedPostId)
            destVC?.setController(controller: controller, dewashData: self.dewashData)
            destVC?.setToken(token: self.dewashData?.getToken())
        }
        else if (segue.identifier == Constants.PropNames.post_automodes_segue) {
            let destVC = segue.destination as? PostAutomodesViewController
            let controller = getController(postId: self.selectedPostId)
            destVC?.setController(controller: controller)
            destVC?.setToken(token: self.dewashData?.getToken())
        }
    }
    
    func getController(postId: String?) -> Controller? {
        for controller in self.posts {
            print(controller._id)
            if (postId == controller._id) {
                return controller
            }
        }
        
        return nil
    }
}

extension ViewController: PostCellDelegate {
    func didTapInfo(postId: String) {
        self.selectedPostId = postId
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: Constants.PropNames.post_info_segue, sender: self)
        }
    }
    
    func didTapModes(postId: String) {
        self.selectedPostId = postId
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: Constants.PropNames.post_modes_segue, sender: self)
        }
    }
    
    func didTapChart(postId: String) {
        self.selectedPostId = postId
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: Constants.PropNames.post_chart_segue, sender: self)
        }
    }
    
    func didTapAutomodes(postId: String) {
        self.selectedPostId = postId
        DispatchQueue.main.async {
            self.performSegue(withIdentifier: Constants.PropNames.post_automodes_segue, sender: self)
        }
    }
}

extension ViewController: UITableViewDataSource, UITableViewDelegate {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.posts.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let post = self.posts[indexPath.row]
        
        let cell = tableView.dequeueReusableCell(withIdentifier: Constants.PropNames.post_cell) as! PostTableViewCell
        
        cell.setPostData(controller: post)
        cell.delegate = self
        return cell
    }
}
