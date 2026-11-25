#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <queue>
using namespace std;

class Employee 
{
    public:
        uint32_t  id;
        string name;
        float salary;

    Employee(){}
    Employee(uint32_t id,string name,float salary)
    {
        this->id = id;
        this->name = name;
        this->salary = salary;
    }

    uint32_t getId() const
    {
        return id;
    }
};

class Customer
{
    public:
        uint32_t  id;
        string name;
        string address;

    Customer(){}
    Customer(uint32_t id,string name,string address)
    {
        this->id = id;
        this->name = name;
        this->address = address;
    }

    uint32_t getId() const
    {
        return id;
    }
};

class Sale
{
    public:
        Customer* customer;
        Employee* salerep;

        uint32_t  id;

        uint32_t employeeid;
        uint32_t customerid;

        float amount;
        time_t date ;

        Sale(){}
        Sale(Customer* customer,Employee* salerep,uint32_t id,float amount)
        {
            this->customer = customer;
            this->salerep = salerep;
            this->amount = amount;
            this->date = time(NULL);
            this->id = id;
            this->employeeid = salerep ? salerep->id : 0;
            this->customerid = customer ? customer->id : 0;
        }

        uint32_t getId() const
        {
            return id;
        }

        time_t getTime() const
        {
            return date;
        }
};

ostream& operator<<(ostream& out, const Employee& e)
{
    out << "[Emp ID: " << e.id
        << ", Name: " << e.name
        << ", Salary: " << e.salary << "]";
    return out;
}

ostream& operator<<(ostream& out, const Customer& c)
{
    out << "[Cus ID: " << c.id
        << ", Name: " << c.name
        << ", Address: " << c.address << "]";
    return out;
}

ostream& operator<<(ostream& out, const Sale& s)
{
    out << "[Sale ID: " << s.id
        << ", Customer ID: " << s.customerid
        << ", Employee ID: " << s.employeeid
        << ", Amount: " << s.amount << "]";
    return out;
}

/*
    A template is a blueprint for creating functions or classes that can work with multiple data types.
    Generic code means writing code that can work with different data types or different kinds of input without rewriting the same logic repeatedly.
    in simple : write once and reuse the same code for multiple data types.
*/
template <typename T> class BinaryTree
{
    private:
        struct Node
        {
            T data;
            Node* left;
            Node* right;
            int height;

            Node(const T& data)
            {
                this->data = data;
                this->left = NULL;
                this->right = NULL;
                this->height = 1;
            }
        };
        Node* root = NULL;

        /*
        //Insert a Node by compairing Ids.
        Node* insertNode(Node *root,const T &value)
        {
            if(root == nullptr)
            {
                return new Node(value);
            }

            if(value.getId() < root->data.getId())
            {
                root->left = insertNode(root->left,value);
            }

            if(value.getId() > root->data.getId())
            {
                root->right = insertNode(root->right,value);
            }

            return root;
        }
        */

        int height(Node* root)
        {
            if(root == NULL)
            {
                return 0;
            }

            return root->height;
        }

        void updateHeight(Node* root)
        {
            root->height = 1 + max(height(root->left),height(root->right)); 
        }

        int checkBalanceFactor(Node* root)
        {
            if(root == NULL)
            {
                return 0;
            }

            return height(root->left) - height(root->right);
        }

        Node* leftRotate(Node* root)
        {
            Node* child = root->right;
            Node* temp = child->left;

            child->left = root;
            root->right = temp;

            updateHeight(root);
            updateHeight(child);

            return child;
        }

        Node* rightRotate(Node* root)
        {
            Node* child = root->left;
            Node* temp = child->right;

            child->right = root;
            root->left = temp;

            updateHeight(root);
            updateHeight(child);

            return child;
        }

        Node* insertNode(Node* root, const T& value)
        {
            if(root == NULL)
            {
                return new Node(value);
            }

            if(value.getId() < root->data.getId())
            {
                root->left = insertNode(root->left,value);
            }

            else if(value.getId() > root->data.getId())
            {
                root->right = insertNode(root->right,value);
            }
            else
            {
                return root;
            }

            updateHeight(root);

            int balance = checkBalanceFactor(root);

            //LL
            if(balance > 1 && value.getId() < root->left->data.getId())
            {
                return rightRotate(root);
            }

            //RR
            if(balance < -1 && value.getId() > root->right->data.getId())
            {
                return leftRotate(root);
            }

            //LR
            if(balance > 1 && value.getId() > root->left->data.getId())
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            //RL
            if(balance < -1 && value.getId() < root->right->data.getId())
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;
        }

        //Search Node by Id
        Node* searchNode(Node* root,uint32_t id) const
        {
            if(root == nullptr)
            {
                return nullptr;
            }

            if(id < root->data.getId())
            {
                return searchNode(root->left, id);
            }

            if(id > root->data.getId())
            {
                return searchNode(root->right, id);
            }

            return root;
        }

        //Min Value
        Node* minVal(Node* root)
        {
            if (root == nullptr)
            return nullptr;

            Node* temp = root;

            while(temp->left != NULL)
            {
                temp = temp->left;
            }
            return temp;
        }

        //Max Value
        Node* maxVal(Node* root)
        {
            if (root == nullptr)
            return nullptr;

            Node* temp = root;

            while(temp->right !=NULL)
            {
                temp = temp->right;
            }
            return temp;
        }

        /*
        //Delete Node
        Node* deleteNode(Node* root,uint32_t id)
        {
            if( root == nullptr) return nullptr;

            if(root->data.getId() == id)
            {
                //0 child
                if(root->left == NULL && root->right == NULL)
                {
                    delete root;
                    return NULL;
                }

                //1 child
                //Left
                if(root->left != NULL && root->right == NULL)
                {
                    Node* temp = root->left;
                    delete root;
                    return temp;
                }

                //Right 
                if(root->right != NULL && root->left == NULL)
                {
                    Node* temp = root->right;
                    delete root;
                    return temp;
                }

                //2child
                if(root->left != NULL && root->right != NULL)
                {
                    T mini = minVal(root->right)->data;
                    root->data = mini;
                    root->right = deleteNode(root->right,mini.getId());
                    return root;
                }
            }
            else if(root->data.getId() > id)
            {
                root->left = deleteNode(root->left,id);
                return root;
            }
            else
            {
                root->right = deleteNode(root->right,id);
                return root;
            }

            return root;
        }
        */



        Node* deleteNode(Node* root, uint32_t id)
        {
            if(root == NULL)
            {
                return NULL;
            }

            if(root->data.getId() > id)
            {
                root->left = deleteNode(root->left,id);
            }
            else if(root->data.getId() < id)
            {
                root->right = deleteNode(root->right,id);
            }
            else
            {
                //0 Child
                if(root->left == NULL && root->right == NULL)
                {
                    delete root;
                    return NULL;
                }
    
                //1 Child 
                //Left
                if(root->left != NULL && root->right == NULL)
                {
                    Node* temp = root->left;
                    delete root;
                    return temp;
                }
                //1Child
                //Right
                if(root->right != NULL && root->left == NULL)
                {
                    Node* temp = root->right;
                    delete root;
                    return temp;
                }
                //2 Child
                if(root->left != NULL && root->right != NULL)
                {
                    T mini = minVal(root->right)->data;
                    root->data = mini;
    
                    root->right = deleteNode(root->right,mini.getId());
    
                }
            }

            updateHeight(root);

            int balance = checkBalanceFactor(root);

            if(balance > 1)
            {
                //LL
                if(checkBalanceFactor(root->left) >= 0)
                {
                    return rightRotate(root);
                }    
                //LR

                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            if(balance < -1)
            {
                //RR
                if(checkBalanceFactor(root->right) <= 0)
                {
                    return leftRotate(root);
                }
                //RL
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }

            return root;

        }

        void inOrder(Node* root,std::vector<T> &temp)const
        {
            if(root == NULL)
            {
                return;
            }

            inOrder(root->left,temp);
            temp.push_back(root->data);
            inOrder(root->right,temp);
        }

        void postOrder(){};

        void preOrder(){};

        void levlOrderTraversal(Node* root) const
        {
            if(root == nullptr)
            {
                return ;
            }

            queue<Node*>q;
            q.push(root);
            q.push(NULL);

            while(!q.empty())
            {
                Node* temp = q.front();
                q.pop();

                if(temp == NULL)
                {
                    cout<<endl;
                    if(!q.empty())
                    {
                        q.push(NULL);
                    }
                }
                else
                {
                    cout<<temp->data<<" ";
                    if(temp->left)
                    {
                        q.push(temp->left);
                    }
                    if(temp->right)
                    {
                        q.push(temp->right);
                    }
                }
            }
        }

        // Clear Tree
        void clear(Node* root)
        {
            if(root == NULL) return;

            clear(root->left);
            clear(root->right);

            delete root;
        }
    
    public:
        BinaryTree(){};
        ~BinaryTree()
        {
            clear(root);
        }

        void insert(const T &value)
        {
            root = insertNode(root, value);
        }

        bool search(uint32_t id) const
        {
            return searchNode(root, id) != nullptr;
        }

        // Find will returns the actual object
        T* find(uint32_t id)
        {
            Node* node = searchNode(root, id);
            return node ? &node->data : nullptr;  //Returns an object that can be modified.
        }

        const T* find(uint32_t id) const
        {
            Node* node = searchNode(root, id);
            return node ? &node->data : nullptr; //Returns an object that cannot be modified through the returned pointer.
        }

        bool remove(uint32_t id)
        {
            if(searchNode(root,id) == nullptr)
            {
                return false;
            }

            root = deleteNode(root, id);
            return true;
        }

        bool empty() const
        {
            return root == nullptr;
        }

        vector<T> inOrder() const
        {
            vector<T> result;
            inOrder(root, result);
            return result;
        }

        T getMin() const
        {
            Node* temp = minVal(root);
            if(temp == nullptr)
            {
                throw runtime_error("Tree is empty");
            }
            return temp->data;
        }

        T getMax() const
        {
            Node* temp = maxVal(root);
            if(temp == nullptr)
            {
                throw runtime_error("This is empty");
            }
            return temp->data;
        }

        void clear()
        {
            clear(root);
            root = nullptr;
        }

        void levelOrder() const
        {
            levlOrderTraversal(root);
        }

};

/*
    Writes any fixed-size, trivially copyable value into a byte array.
    Works for: uint32_t, int32_t, float, double, uint64_t
    Does not work for:  std::string, pointers, Employee, Customer, Sale
*/

template <typename T>
void writeByte(vector<uint8_t>& out, const T& val)
{
    static_assert(is_trivially_copyable<T>::value,
        "writeFixed supports only trivially copyable types");       // Check for type  

    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&val);  //treats the memory address of val as a pointer to individual bytes.
    out.insert(out.end(), bytes, bytes + sizeof(T));                //Coppy all bytes from of  the val into vector 
}

/*
    Reads any fixed-size, trivially copyable value from a byte array.
    The position advances by sizeof(T).
    It checks that enough bytes remain before reading.
*/
template <typename T>
T readByte(const vector<uint8_t>& in, size_t& pos)
{
    static_assert(is_trivially_copyable<T>::value,
        "readFixed supports only trivially copyable types");

    if (pos + sizeof(T) > in.size())
        throw runtime_error("Corrupt or truncated serialized data");

    T value;
    memcpy(&value, in.data() + pos, sizeof(T));
    pos += sizeof(T);

    return value;
}

/*
    Writes a string as:
        [4-byte length][string bytes]

    std::string is not trivially copyable, so it must not use memcpy
    on the whole string object.
*/

void writeString(vector<uint8_t>& out, const string& text)
{
    writeByte<uint32_t>(out, static_cast<uint32_t>(text.size()));

    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(text.data());  
    out.insert(out.end(), bytes, bytes + text.size());  
}

/*
    Reads a string written by writeString().
    It first reads the length, then reads exactly that many bytes.
*/

string readString(const vector<uint8_t>& in, size_t& pos)
{
    uint32_t length = readByte<uint32_t>(in, pos);

    if (pos + length > in.size())
        throw runtime_error("Corrupt string length in serialized data");  //Check whether enough bytes are available

    string text(reinterpret_cast<const char*>(in.data() + pos), length);
    pos += length;

    return text;
}

void serializeEmployee(const Employee& employee, vector<uint8_t>& out)
{
    writeByte<uint32_t>(out, employee.id);
    writeString(out, employee.name);
    writeByte<float>(out, employee.salary);
}

Employee deserializeEmployee(const vector<uint8_t>& in,size_t& pos)
{
    Employee employee;

    employee.id = readByte<uint32_t>(in,pos);
    employee.name = readString(in, pos);
    employee.salary = readByte<float>(in, pos);

    return employee;
}

void serializeCustomer(const Customer& customer, vector<uint8_t>& out)
{
    writeByte<uint32_t>(out, customer.id);
    writeString(out, customer.name);
    writeString(out, customer.address);
}

Customer deserializeCustomer(const vector<uint8_t>&in, size_t& pos)
{
    Customer customer;

    customer.id = readByte<uint32_t>(in ,pos);
    customer.name = readString(in, pos);
    customer.address = readString(in, pos);

    return customer;
}

void serializeSale(const Sale& sale, vector<uint8_t>& out)
{
    writeByte<uint32_t>(out, sale.id);
    writeByte<uint32_t>(out, sale.employeeid);
    writeByte<uint32_t>(out, sale.customerid);
    writeByte<float>(out, sale.amount);

    uint64_t date = static_cast<uint64_t>(sale.date);
    writeByte<uint64_t>(out, date);
}

Sale deserializeSale(const vector<uint8_t>&in, size_t& pos)
{
    Sale sale;

    sale.id = readByte<uint32_t>(in,pos);
    sale.employeeid = readByte<uint32_t>(in, pos);
    sale.customerid = readByte<uint32_t>(in, pos);
    sale.amount = readByte<float>(in, pos);

    uint64_t date = readByte<uint64_t>(in, pos);
    sale.date = static_cast<time_t>(date);

    return sale;
} 

// Global data structures
static BinaryTree<Employee> employeeTree;
static BinaryTree<Customer> customerTree;
static BinaryTree<Sale> saleTree;


uint32_t nextEmployeeId = 1;
uint32_t nextCustomerId = 1;
uint32_t nextSaleId = 1;

/*
    Serialization converts in-memory objects into a transferable or storable representation, and 
    deserialization reconstructs those objects from that representation.
*/

vector<uint8_t> serialize()
{
    vector<uint8_t> data;

    vector<Employee> employees = employeeTree.inOrder();
    vector<Customer> customers = customerTree.inOrder();
    vector<Sale> sales = saleTree.inOrder();

    writeByte<uint32_t>( data, employees.size() );
    for(const Employee& employee : employees)
    {
        serializeEmployee(employee, data);
    }

    writeByte<uint32_t>( data, customers.size() );
    for(const Customer& customer : customers)
    {
        serializeCustomer(customer, data);
    }

    writeByte<uint32_t>( data, sales.size() );
    for(const Sale& sale : sales)
    {
        serializeSale(sale, data);
    }

    writeByte<uint32_t>(data, nextEmployeeId);
    writeByte<uint32_t>(data, nextCustomerId);
    writeByte<uint32_t>(data, nextSaleId);

    return data;
}

void deserialize(const vector<uint8_t>& data)
{
    employeeTree.clear();
    customerTree.clear();
    saleTree.clear();

    size_t pos = 0;

    uint32_t employeeCount = readByte<uint32_t>(data, pos);
    for(uint32_t i=0; i< employeeCount; i++)
    {
        Employee employee = deserializeEmployee(data, pos);
        employeeTree.insert(employee);
    }

    uint32_t customerCount = readByte<uint32_t>(data, pos);
    for(uint32_t i=0;i<customerCount;i++)
    {
        Customer customer = deserializeCustomer(data, pos);
        customerTree.insert(customer);
    }

    uint32_t saleCount = readByte<uint32_t>(data, pos);
    for(uint32_t i = 0; i< saleCount; i++)
    {
        Sale sale = deserializeSale(data, pos);

        sale.customer = customerTree.find(sale.customerid);
        sale.salerep = employeeTree.find(sale.employeeid);

        if(sale.customer != nullptr && sale.salerep != nullptr)
        {
            saleTree.insert(sale);
        }
    }

    nextEmployeeId = readByte<uint32_t>(data, pos);
    nextCustomerId = readByte<uint32_t>(data, pos);
    nextSaleId = readByte<uint32_t>(data, pos);
}

void writeFile() {
    vector<uint8_t> data = serialize();

    FILE* file = fopen("Data.bin", "wb");

    if (file == nullptr) {
        cout << "Unable to open Data.bin for writing.\n";
        return;
    }

    if (!data.empty()) {
        fwrite(data.data(), 1, data.size(), file);
    }

    fclose(file);

    cout << "Data saved to Data.bin.\n";
}

void loadFile() {
    FILE* file = fopen("Data.bin", "rb");

    if (file == nullptr) {
        cout << "Data.bin not found. Starting with empty data.\n";
        return;
    }

    fseek(file, 0, SEEK_END); //moves the pointer to the end.
    long fileSize = ftell(file); //returns the current position of the file pointer.
    fseek(file, 0, SEEK_SET); //Move the pointer back to the beginning

    vector<uint8_t> data(static_cast<size_t>(fileSize));

    if (fileSize > 0) {
        fread(data.data(), 1, static_cast<size_t>(fileSize), file);
    }

    fclose(file);

    deserialize(data);

    cout << "Data loaded from Data.bin.\n";
}


void addEmployee()
{
    string name;
    float salary;

    cout<<"Enter employee name : ";
    getline(cin >> ws, name);
    
    cout<<"Enter Employee Salary : ";
    cin >> salary;
    
    Employee employee(nextEmployeeId++,name,salary);
    
    employeeTree.insert(employee);
    writeFile();
    cout<<"Employee added sucessfully. ID: "<<employee.getId()<<endl;
}

void addCustomer()
{
    string name;
    string address;
    
    cout<<"Enter customer name: ";
    getline(cin >> ws, name);
    
    cout<<"Enter customer address: ";
    getline(cin >> ws, address);
    
    Customer customer(nextCustomerId++, name , address);
    
    customerTree.insert(customer);
    writeFile();
    cout<<"Customer add Sucessfully. ID: "<< customer.getId()<<endl;
}

void addSale()
{
    uint32_t customerId;
    uint32_t employeeId;
    float amount;
    time_t date;
    
    cout<<"Enter customer ID : ";
    cin >> customerId;
    
    cout<<"Enter the employee ID : ";
    cin >> employeeId;
    
    
    if(customerTree.find(customerId) == nullptr)
    {
        cout<<"Customer not found!"<<endl;
        return;
    }
    
    if(employeeTree.find(employeeId) == nullptr)
    {
        cout<<"Empoyee not found!"<<endl;
        return;
    }
    
    Customer* customer = customerTree.find(customerId);
    Employee* employee = employeeTree.find(employeeId);
    
    cout<<"Enter sale amount : ";
    cin>>amount;
    
    Sale sale(customer, employee,nextSaleId++, amount);
    
    saleTree.insert(sale);
    writeFile();
    cout<<"Sale add sucessfully. ID : "<<sale.getId()<<endl;
}

/*
Employee* findEmployeeByName(const string& name)
{
    vector<Employee> employees = employeeTree.inOrder();

    for (const Employee& emp : employees)
    {
        if (emp.name == name)
        {
            return employeeTree.find(emp.id);
        }
    }

    return nullptr;
}
*/

template <typename T>
T* findByName(BinaryTree<T>& tree, const string& name)
{
    vector<T> records = tree.inOrder();

    for (const T& val : records)
    {
        if (val.name == name)
        {
            return tree.find(val.getId());
        }
    }

    return nullptr;
}
// Search Employee By Name with its sales details

void Info()
{
    string name;

    cout << "Enter Employee Name: ";
    cin >> name;

    Employee* emp = findByName(employeeTree,name);

    if (emp == nullptr)
    {
        cout << "Employee not found.\n";
        return;
    }

    cout<<"Employee Detail : \n";

    cout << "Employee Id: " << emp->id 
        << " | Employee Name: " << emp->name 
        << " | Employee Salary: " << emp->salary << "\n";

    vector<Sale> sales = saleTree.inOrder();

    float totalAmount = 0.0f;
    int numberOfSales = 0;

    for (const Sale& sale : sales)
    {
        if (sale.employeeid == emp->id)
        {
            cout << "Sale ID: " << sale.id 
                << " | Amount: " << sale.amount 
                << " | Customer Name: "<< sale.customer->name<<endl;

            totalAmount += sale.amount;
            numberOfSales++; 
        }
    }

    cout<<"\nTotal Sales : "<<totalAmount ;
    cout<<"\nTotal Number of Sales : "<<numberOfSales<<"\n\n";
}

void listEmployees()
{
    vector<Employee> employees = employeeTree.inOrder();

    for (const Employee& emp : employees)
    {
        cout << "ID: " << emp.id << " | Name: " << emp.name
             << " | Salary: " << emp.salary << endl;
    }
}


void listCustomers()
{
    vector<Customer> customers = customerTree.inOrder();
    
    for(const Customer& cus : customers)
    {
        cout<<"CusID: "<<cus.id<< " | Customer_Name : "<<cus.name 
        <<" | Customer_Address : "<<cus.address << endl;
    }
};

/*
void listSales()
{
    vector<Sale> sales = saleTree.inOrder();

    for (const Sale& sale : sales)
    {
        time_t saleTime = sale.getTime();

        cout << "Sale ID: " << sale.id;

        cout << " | Customer: "<< sale.customer->name 
             << " | Sales Representative: "<< sale.salerep->name
             << " | Amount: " << sale.amount
             << " | Date: " << ctime(&saleTime) << endl;
    }
}
*/

void listSales()
{
    for (const Sale& sale : saleTree.inOrder())
    {
        const Customer* customer = customerTree.find(sale.customerid);
        const Employee* employee = employeeTree.find(sale.employeeid);

        time_t saleTime = sale.getTime();

        cout << "Sale ID: " << sale.id
             << " | Customer: "
             << (customer ? customer->name : "Unknown")
             << " | Sales Representative: "
             << (employee ? employee->name : "Unknown")
             << " | Amount: " << sale.amount
             << " | Date: " << ctime(&saleTime);
    }
}

void showEmployeeTree()
{
    cout<<"Employee Tree : \n";
    employeeTree.levelOrder();
}

void showCustomerTree()
{
    cout<<"Customer Tree : \n";
    customerTree.levelOrder(); 
}

void showSaleTree()
{
    cout<<"Sales Tree : \n";
    saleTree.levelOrder();
}

bool employeeHasSales(uint32_t employeeId)
{
    vector<Sale> sales = saleTree.inOrder();

    for(const Sale& sale : sales)
    {
        if(sale.employeeid == employeeId)
        {
            return true;
        }
    }
    return false;
}

bool customerHasSales(uint32_t customerId)
{
    vector<Sale> sales = saleTree.inOrder();

    for(const Sale& sale : sales)
    {
        if(sale.customerid == customerId)
        {
            return true;
        }
    }
    return false;
}

void deleteEmployee()
{
    uint32_t id;

    cout<<"Enter Employee Id to delete : ";
    cin>> id;

    if(employeeTree.find(id) == NULL)
    {
        cout<<"Employee Not Found! \n";
        return;
    }

    if(employeeHasSales(id))
    {
        cout<<"Cannot delete employee. Delete their sales first.\n";
        return;
    }

    employeeTree.remove(id);
    writeFile();
    cout<<"Employee Deleted Sucessfully.\n";
}

void deleteCustomer()
{
    uint32_t id;

    cout<<"Enter Customer Id to Delete : ";
    cin>>id;

    if(customerTree.find(id) == NULL)
    {
        cout<<"Customer Not Found!\n";
        return;
    }
    if(customerHasSales(id))
    {
        cout<<"Cannot delete customer. Delete their sles first.\n";
        return;
    }

    customerTree.remove(id);
    writeFile();
    cout<<"Customer Deleted Sucessfully.\n";
}

void deleteSale()
{
    uint32_t id;
    cout<<"Enter Sale Id to delete : ";
    cin>>id;

    if(saleTree.find(id) == NULL)
    {
        cout<<"Sale not Found!\n";
        return;
    }

    if(saleTree.remove(id))
    {
        writeFile();
        cout<<"Sale deleted sucessfully. \n";
    }
    else
    {
        cout<<"Sale could not be deleted. \n";
    }
}

void menu()
{
    int choice;

    do
    {
        cout<<"_____Management System_____\n";
        cout<<"1. Add Employee\n";
        cout<<"2. Add Customer\n";
        cout<<"3. Add Sale\n";
        cout<<"4. List of Employee's\n";
        cout<<"5. List of Customer's\n";
        cout<<"6. List of Sale's\n";
        cout<<"7. Search Employee Information\n";
        cout<<"8. Employee Tree\n";
        cout<<"9. Customer Tree\n";
        cout<<"10. Sale Tree\n";
        cout<<"11. Delete Employee \n";
        cout<<"12. Delete Customer \n";
        cout<<"13. Delete Sale \n";
        cout<<"0. Exit\n";

        cout<<"Enter Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addEmployee();
                break;
            case 2:
                addCustomer();
                break;
            case 3:
                addSale();
                break;
            case 4:
                listEmployees();
                break;
            case 5:
                listCustomers();
                break;
            case 6:
                listSales();
                break;
            case 7:
                Info();
                break;
            case 8:
                showEmployeeTree();
                break;
            case 9:
                showCustomerTree();
                break;
            case 10:
                showSaleTree();
                break;
            case 11:
                deleteEmployee();
                break;
            case 12:
                deleteCustomer();
                break;
            case 13:
                deleteSale();
                break;
            case 0 :
                cout<<"Exiting ..\n";
                break;
            default:
                cout<<"Invalid choice!\n";
        }
    }while (choice != 0);
}


int main()
{
    loadFile();
    menu();
    writeFile();
}

    /*BinaryTree<Employee> employees;

    Employee e1(50, "John", 50000);
    Employee e2(30, "David", 40000);
    Employee e3(70, "Smith", 60000);
    Employee e4(20, "Alex", 35000);
    Employee e5(40, "Sam", 45000);


    employees.add(e1);
    employees.add(e2);
    employees.add(e3);
    employees.add(e4);
    employees.add(e5);

  
    cout << "\nInorder Traversal:\n";
    employees.inorder();

   
    cout << "\nSearching Employee ID 30:\n";

    Employee* result = employees.search(30);

    if (result != nullptr)
    {
        cout << "Name: " << result->name << endl;
        cout << "Salary: " << result->salary << endl;
    }
    else
    {
        cout << "Employee not found\n";
    }
    */
//-------------------------------------------------------------------
    /*
    BinaryTree<Customer> customers;

    Customer c1(50, "John", "Mumbai");
    Customer c2(30, "David", "Pune");
    Customer c3(70, "Smith", "Delhi");
    Customer c4(20, "Alex", "Goa");
    Customer c5(40, "Sam", "Bangalore");

  
    customers.add(c1);
    customers.add(c2);
    customers.add(c3);
    customers.add(c4);
    customers.add(c5);


    cout << "\nCustomer Inorder Traversal:\n";
    customers.inorder();

   
    cout << "\nSearching Customer ID 30:\n";

    Customer* result = customers.search(30);

    if (result != nullptr)
    {
        cout << "Name: " << result->name << endl;
        cout << "Address: " << result->address << endl;
    }
    else
    {
        cout << "Customer not found\n";
    }

  
    cout << "\nDeleting Customer ID 30:\n";
    customers.remove(30);

  
    cout << "\nAfter Deletion:\n";
    customers.inorder();
    
    */

//-------------------------------------------------------------------
    /*
    BinaryTree<Sale> sales;

  
    Employee e1(1, "John", 50000);
    Employee e2(2, "David", 40000);

   
    Customer c1(1, "Smith", "Mumbai");
    Customer c2(2, "Alex", "Pune");

    
    Sale s1(50, &c1, &e1, 5000, time(nullptr));
    Sale s2(30, &c2, &e2, 8000, time(nullptr));
    Sale s3(70, &c1, &e2, 3000, time(nullptr));
    Sale s4(20, &c2, &e1, 6000, time(nullptr));
    Sale s5(40, &c1, &e1, 9000, time(nullptr));

    
    sales.add(s1);
    sales.add(s2);
    sales.add(s3);
    sales.add(s4);
    sales.add(s5);

    
    cout << "\nSale Inorder Traversal:\n";
    sales.inorder();

    
    cout << "\nSearching Sale ID 30:\n";

    Sale* result = sales.search(30);

    if (result != nullptr)
    {
        cout << "Sale ID: " << result->id << endl;
        cout << "Customer: " << result->customer->name << endl;
        cout << "Sales Representative: " << result->salerep->name << endl;
        cout << "Amount: " << result->amount << endl;
    }
    else
    {
        cout << "Sale not found\n";
    }
*/
