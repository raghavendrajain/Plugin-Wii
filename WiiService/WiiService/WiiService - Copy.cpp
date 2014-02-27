#include "SIGService.h"
#include <boost/python.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <string>
#include <conio.h> 
#define ESC 27



namespace py = boost::python;  
using namespace std; 


std::string parse_python_exception(); // functional declaration for exception handling

template <typename T> string tostr(const T& t) { ostringstream os; os<<t; return os.str(); } // template to convert double variables to string


class Wii_Service : public sigverse::SIGService  
  {  
public:  
    Wii_Service(std::string name);  
    ~Wii_Service();  
    double onAction();  
    void onRecvMsg(sigverse::RecvMsgEvent &evt);  
//private: Joystick*  JS; //pointer to joystick object  
//private: HWND hWnd;   
 };  
  Wii_Service::Wii_Service(std::string name) : SIGService(name){  
            //JS = new Joystick();  
            //hWnd = NULL;  
    };  
Wii_Service::~Wii_Service()  
 {  
    this->disconnect();  
 } 
void Wii_Service::onRecvMsg(sigverse::RecvMsgEvent &evt)  
{  
}



double Wii_Service::onAction()  
{  
	
		Py_Initialize();

	try{

		py::object main_module = py::import("__main__");  
		py::object main_namespace = main_module.attr("__dict__");
		py::exec("print 'Hello, world'", main_namespace);
		py::exec("print 'Hello, world'[3:5]", main_namespace);
		py::exec("print '.'.join(['1','2','3'])", main_namespace);
		//py::exec("import pygame", main_namespace);
		py::exec("import getDataFromWii as gt", main_namespace);
		py::exec("a=gt.withYield()", main_namespace);

	    //py::exec("import mouseGenerator as mG", main_namespace);
		
		//srv.connect("192.168.89.133", 9000);  
		// connect to the server using host/port
		// Send the message "Hello" to the "man_000" entity  

		int pos_n= 1000;
		float dataArray[6]={0,0,0,0,0,0};
		std::string msgFromWii("");
		char tmp[128]={0};
 

		boost::python::list xl;
		// char c=getch();
		std::cout<<"press esc to exit! "<<std::endl;
		int key=0;
		char c;
		//while (getche() != 27){
		//for(unsigned int i=0; i<pos_n; i++) {
		//do{
			int flag=1;
			//while (true){
				//c=getch();
				//if (c==27)
					//break;
				py::object listOfPos = py::eval("next(a)", main_namespace);
				//py::object listOfPos = py::exec("print next(a)", main_namespace);
				//std::cout << py::extract<double>(listOfPos[0]) << std::endl;
				//std::cout << py::extract<double>(listOfPos[1]) << std::endl
				//py::exec("print 'the next is', next(a)", main_namespace);
				int lenList=len((listOfPos));
				//std::cout << " length is " << lenList <<std::endl;
				if (lenList==6){
					for(unsigned int i=0; i<lenList; i++){
					//std::cout << py::extract<double>((listOfPos)[i])<< std::endl;
					//std::cout<<"The possition array before  is" << dataArray[0] << "  and   " << dataArray[1] << std::endl;
					//std::cout<<py::extract<double>((listOfPos)[0]) <<std::endl;
					//std::cout<<py::extract<double>((listOfPos)[1]) <<std::endl;
					dataArray[i] = py::extract<double>((listOfPos)[i]);	
					}
				}
				else {
				  dataArray[0]=0;
				  dataArray[1]=0;
				  dataArray[2]=0;
				  dataArray[3]=0;
				  dataArray[4]=0;
				  dataArray[5]=0;

				}


			sprintf(tmp,  "%f,%f,%f,%f,%f,%f", dataArray[0], dataArray[1], dataArray[2], dataArray[3], dataArray[4], dataArray[5]);
			//std::cout<<"At i: " << i <<std::endl; 
			std::cout<<"The orientation data: Roll, Pitch, Yaw is" << dataArray[0] << " , " << dataArray[1] << " , " << dataArray[2]<<std::endl;
			std::cout<<"The acceleration: x, y, z is" << dataArray[3] << " , " << dataArray[4] << " , " << dataArray[5]<<std::endl;
			msgFromWii = std::string(tmp);
			std::cout << "The sent message from Wii is: " << msgFromWii << std::endl; 
			//srv.sendMsg("robot_test", msgFromWii);
			this->sendMsg("GrabTool", msgFromWii);
		
	}

    catch(boost::python::error_already_set const &){
        // Parse and output the exception
        std::string perror_str = parse_python_exception();
        std::cout << "Error in Python: " << perror_str << std::endl;
    }


	// disconnect from the server
	//srv.disconnect();
	return 0.00001;
}



int main(int argc, char** argv)
{
	// Create an instance of the service class with the specified service name
	Wii_Service srv("MyService");
/*
	Py_Initialize();

	try{

		py::object main_module = py::import("__main__");  
		py::object main_namespace = main_module.attr("__dict__");
		py::exec("print 'Hello, world'", main_namespace);
		py::exec("print 'Hello, world'[3:5]", main_namespace);
		py::exec("print '.'.join(['1','2','3'])", main_namespace);
		//py::exec("import pygame", main_namespace);
		py::exec("import getDataFromWii as gt", main_namespace);
		py::exec("a=gt.withYield()", main_namespace);

	    //py::exec("import mouseGenerator as mG", main_namespace);
	    std::string host = argv[1];
		unsigned short port = (unsigned short)(atoi(argv[2]));  
		srv.connect(host, port); 
		
		//srv.connect("192.168.89.133", 9000);  
		// connect to the server using host/port
		// Send the message "Hello" to the "man_000" entity  

		int pos_n= 1000;
		float dataArray[6]={0,0,0,0,0,0};
		std::string msgFromWii("");
		char tmp[128]={0};
 

		boost::python::list xl;
		// char c=getch();
		std::cout<<"press esc to exit! "<<std::endl;
		for(unsigned int i=0; i<pos_n; i++) {
			int flag=1;
			//while (true){
				py::object listOfPos = py::eval("next(a)", main_namespace);
				//py::object listOfPos = py::exec("print next(a)", main_namespace);
				//std::cout << py::extract<double>(listOfPos[0]) << std::endl;
				//std::cout << py::extract<double>(listOfPos[1]) << std::endl
				//py::exec("print 'the next is', next(a)", main_namespace);
				int lenList=len((listOfPos));
				//std::cout << " length is " << lenList <<std::endl;
				if (lenList==6){
					for(unsigned int i=0; i<lenList; i++){
					//std::cout << py::extract<double>((listOfPos)[i])<< std::endl;
					//std::cout<<"The possition array before  is" << dataArray[0] << "  and   " << dataArray[1] << std::endl;
					//std::cout<<py::extract<double>((listOfPos)[0]) <<std::endl;
					//std::cout<<py::extract<double>((listOfPos)[1]) <<std::endl;
					dataArray[i] = py::extract<double>((listOfPos)[i]);	
					}
				}
				else {
				  dataArray[0]=0;
				  dataArray[1]=0;
				  dataArray[2]=0;
				  dataArray[3]=0;
				  dataArray[4]=0;
				  dataArray[5]=0;

				}


			sprintf(tmp,  "%f,%f,%f,%f,%f,%f", dataArray[0], dataArray[1], dataArray[2], dataArray[3], dataArray[4], dataArray[5]);
			std::cout<<"At i: " << i <<std::endl; 
			std::cout<<"The orientation data: Roll, Pitch, Yaw is" << dataArray[0] << " , " << dataArray[1] << " , " << dataArray[2]<<std::endl;
			std::cout<<"The acceleration: x, y, z is" << dataArray[3] << " , " << dataArray[4] << " , " << dataArray[5]<<std::endl;
			msgFromWii = std::string(tmp);
			std::cout << "The sent message from Wii is: " << msgFromWii << std::endl; 
			//srv.sendMsg("robot_test", msgFromWii);
			srv.sendMsg("GrabTool", msgFromWii);
		//}

		std::cout<<"exited: "<<std::endl;
	
	}

	}

    catch(boost::python::error_already_set const &){
        // Parse and output the exception
        std::string perror_str = parse_python_exception();
        std::cout << "Error in Python: " << perror_str << std::endl;
    }


	// disconnect from the server
	srv.disconnect();
*/
	// connect to the server using host/port
	std::string host = argv[1];
	unsigned short port = (unsigned short)(atoi(argv[2]));  
	srv.connect(host, port); 
	srv.startLoop();

	return 0;
}




std::string parse_python_exception(){
    PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
    // Fetch the exception info from the Python C API
    PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);

    // Fallback error
    std::string ret("Unfetchable Python error");
    // If the fetch got a type pointer, parse the type into the exception string
    if(type_ptr != NULL){
        py::handle<> h_type(type_ptr);
        py::str type_pstr(h_type);
        // Extract the string from the boost::python object
        py::extract<std::string> e_type_pstr(type_pstr);
        // If a valid string extraction is available, use it 
        //  otherwise use fallback
        if(e_type_pstr.check())
            ret = e_type_pstr();
        else
            ret = "Unknown exception type";
    }
    // Do the same for the exception value (the stringification of the exception)
    if(value_ptr != NULL){
        py::handle<> h_val(value_ptr);
        py::str a(h_val);
        py::extract<std::string> returned(a);
        if(returned.check())
            ret +=  ": " + returned();
        else
            ret += std::string(": Unparseable Python error: ");
    }
    // Parse lines from the traceback using the Python traceback module
    if(traceback_ptr != NULL){
        py::handle<> h_tb(traceback_ptr);
        // Load the traceback module and the format_tb function
        py::object tb(py::import("traceback"));
        py::object fmt_tb(tb.attr("format_tb"));
        // Call format_tb to get a list of traceback strings
        py::object tb_list(fmt_tb(h_tb));
        // Join the traceback strings into a single string
        py::object tb_str(py::str("\n").join(tb_list));
        // Extract the string, check the extraction, and fallback in necessary
        py::extract<std::string> returned(tb_str);
        if(returned.check())
            ret += ": " + returned();
        else
            ret += std::string(": Unparseable Python traceback");
    }
    return ret;
}
