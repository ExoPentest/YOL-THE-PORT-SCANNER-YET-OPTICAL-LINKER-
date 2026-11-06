// ALL LIBRARIES
#include <iostream>
#include <string>
#include <sys/time.h>
#include <list>
#include <algorithm>
#include <cctype>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;  
// ALL VARIABLES
list <int> SELECTED_NUMBERS_VALID = {1};
int minimum_port_number_selected_for_number_1,maximum_port_number_selected_for_1;
int selected_port_number_minimum_for_1;
int SELECTED_NUMBER;
string IPV4;
string IPV6;


// Main Scanner
int main() {
    cout << "\n=========================================================\n" ;
    cout << "\n=========================================================\n" ;
    cout << "\n=========================================================\n" ;
    cout << "\n=================== YOL VERSION 0.1 =====================\n" ;
    cout << "\n=================== YET OPTICAL LINKER ==================\n" ;
    cout << "\n=========================================================\n" ;
    cout << "\n=========================================================\n" ;
    cout << "\n                                                         \n" ;
    cout << "\n==================LIST OF ACTIONS========================\n" ;
    cout << "[1] Port Scanning Ranger" ;
    // AS OF VERSION 1 ONLY 1 ACTION IS AVAILABLE CURRENTLY
    cout << "\n=========================================================\n" ;
    cout << "                                                         " ;
    cout << "\n[*] To Continue,Please select one action corresponding to the Number :-\n" ;
    cin  >> SELECTED_NUMBER;
    // Error Handling
    auto finder = find(SELECTED_NUMBERS_VALID.begin(),SELECTED_NUMBERS_VALID.end(),SELECTED_NUMBER) ;
    if (finder == SELECTED_NUMBERS_VALID.end()) {
        cout << "\n[*] Please Include a Valid Action Number\n" ;
        return 1 ;
    } else if (isalpha(SELECTED_NUMBER)) {
        cout << "\n[*] Please Type only Corresponding Number";
    }
    
    
    if (SELECTED_NUMBER == 1) {
        cout << "\n[*] Proceeding to Next Step\n";
        cout << "\n========================================================\n" ;
        cout << "[*] IP : " ;
        cin  >> IPV4        ;
        cout << "\n[*] Minimum Port Range : " ;
        cin  >> minimum_port_number_selected_for_number_1 ;
        cout << "\n[*] Maximum Port Range : " ;
        cin  >> maximum_port_number_selected_for_1;
        cout << "\n=======================================================\n" ;
        for (selected_port_number_minimum_for_1 = minimum_port_number_selected_for_number_1 ; selected_port_number_minimum_for_1 <= maximum_port_number_selected_for_1 ; selected_port_number_minimum_for_1++) {
            int sock_for_connection = socket(AF_INET,SOCK_STREAM,0) ;
            
            if (sock_for_connection == 0) {
                cout << "\n[*] Socket Established\n" ;
                
            } else {
                cout << "\n[*] Socket Establishment Failed\n" ;
                
            }
            
            sockaddr_in server = {} ;
            // Tables Fill
            server.sin_family = AF_INET ;
            server.sin_port   = htons(selected_port_number_minimum_for_1) ; 
            
            struct timeval timeout ;
            timeout.tv_sec = 2;
            timeout.tv_usec = 0;
            setsockopt(sock_for_connection,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout)) ;
            
            inet_pton(AF_INET,IPV4.c_str(),
                      &server.sin_addr) ;
                      
                      int result_for_connection = connect(sock_for_connection,
                                                          (sockaddr*)&server,
                                                          sizeof(server)) ;
                                                          if (result_for_connection != 0) {
                                                              cout << "\n[*] Connection Establishment Failed.\n" ; 
                                                              close(sock_for_connection) ; 
                                                              continue ; 
                                                          }
                                                          char buffer[1024] = {0} ;
                                                          ssize_t bytes = recv(sock_for_connection, buffer, sizeof(buffer) - 1, 0) ;
                                                          if (bytes == 0) {
                                                              cout << "\n[*] No Banner Received\n" ;
                                                              timeout.tv_sec = 2;
                                                          }
                                                          
                                                          if ( result_for_connection == 0 && bytes != 0 ) {
                                                              buffer[bytes] = '\0' ; 
                                                              cout << "\n[*] The Port " << selected_port_number_minimum_for_1 << " " << buffer << "is Open!\n" ;
                                                              
                                                              
                                                          } else if ( result_for_connection == 0 ) {
                                                              cout << "\n[*] The Port " << selected_port_number_minimum_for_1 << "is Open" << " " << "NO BANNER FOUND\n" << endl ; 
                                                          }
                                                          
                                                          
                                                          
                                                          close(sock_for_connection) ;
                                                          
                                                          
                                                          
        }  
    } 
}
