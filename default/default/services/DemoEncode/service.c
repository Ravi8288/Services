#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 #include <string.h>   
 #include <errno.h>  
 #include <unistd.h> 
 #include "hpd_log.h"
 #include "hpd_string_api.h"
 /*------------------------------------------ 
 Name:DemoEncode_on_request_callback 
 Purpose: This method is called on receiving the service request and after all search and conditional parameters are processed and before applying service delay time.
 Input:   None 
 Return:  The function controls service time. Return values can be: 
    0 - No service delay time. Override service delay time configure if any 
    -1 - Use service delay time as configured 
    >0 - Use service delay time in milli-seconds returned by this method 
------------------------------------------------*/ 
 int DemoEncode_on_request_callback () 
{   
  char  http_hdr_2[1024];
  char s2[100], s3[100];
  strcpy(s2, ns_eval_string("{Me}"));
  sprintf(http_hdr_2, "Cookie Expired By : %s", strrev(s2,s3));
  ns_set_http_hdr(http_hdr_2);
  ns_save_string(http_hdr_2,"MyStriingParam");
  return -1;   
}
