
/* author zed41
*/

#include<bits/stdc++.h>
#include<string.h>

using namespace std;

class http{

  private:
    string req_type;
    string url;
    //json like structure  to store data and header
    //like key value pair
    map<string,string> data;
    map<string,string> header;

  public:
    //constructor should not be this big zz.
    http(char *raw_req,int display){
      fetch_req(raw_req);
      if(display)
        display_req();
    }

    //return url
    string get_url(){
      return this->url;
    }

    //return req type
    string get_req_type(){
      return this->req_type;
    }

    //get data map
    map<string,string> get_data(){
      return this->data;
    }

    //get header
    map<string,string> get_header(){
      return this->header;
    }

    // display_req
    void display_req(){
      cout<<YEL"\n\t"<<this->req_type<<"\t"BLU<<this->url<<RESET;
      // cout<<YEL"\n\t"<<this->header["Host"]<<RESET"\n";
    }

    //fetch req header and data for post
    void fetch_req(char *raw_req){
      //sexy way to free pointers allocated for temp char*
      char *pointers_to_free[3];
      int i=0;
      char *line=(char *)malloc(sizeof(char)*1000);
      pointers_to_free[i++]=line;
      char *header_ptr;
      char *ptr;
      char *key=(char *)malloc(sizeof(char)*200);
      pointers_to_free[i++]=key;
      char *value=(char *)malloc(sizeof(char)*600);
      pointers_to_free[i++]=value;
      char *line1=strtok_r(raw_req,"\n",&header_ptr);
      this-> req_type=strtok_r(line1," ",&ptr);
      this-> url=strtok_r(ptr," ",&ptr);
      if(this->req_type.compare("GET")==0){
        fetch_data_GET();
      }
      //fetch maps from reqest raw String . cool yo .
      while(1){
        line=strtok_r(header_ptr,"\n",&header_ptr);
        if(line==NULL){
          break;
        }
        key=strtok_r(line,":",&ptr);
        value=strtok_r(ptr,"\n",&ptr);
        if (key == NULL || value == NULL)
          break;
        if(strstr(STD_HEADER,key)!=NULL)
          this->header[key]=value;
        else
          this->data[key]=value;
      }
      // free the pointers you dont want every req to
      // have 1800 char space from your memory .
      for(i=0;i<3;i++)
        free(pointers_to_free[i]);
    }

    //fetch data from url for GET request
    void fetch_data_GET(){
      char *url=new char[this->url.length()+1];
      strcpy(url,this->url.c_str());
      char *header_ptr;
      char *ptr;
      char *pointers_to_free[3];
      int i=0;
      char *key=(char *)malloc(sizeof(char)*100);
      pointers_to_free[i++]=key;
      char *value=(char *)malloc(sizeof(char)*100);
      pointers_to_free[i++]=value;
      char *line=(char *)malloc(sizeof(char)*200);
      pointers_to_free[i++]=line;
      char *url_only=strtok_r(url,"?",&header_ptr);
      this->url=url_only;
      while(1){
        line=strtok_r(header_ptr,"&",&header_ptr);
        if(line==NULL)
          break;
        key=strtok_r(line,"=",&ptr);
        value=strtok_r(NULL,"=",&ptr);
        if(key == NULL || value == NULL)
          break;
        this->data[key]=value;
      }
      for(i=0;i<3;i++)
        free(pointers_to_free[i]);
    }
};
