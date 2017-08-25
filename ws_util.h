string decode(int client){
  int len1,len2,len3;
  int len;
  int len_flag=2;
  string bit_string="";

  char playload_len[2];
  recv(client,playload_len,2,0);
  bit_string.append(bitset<8>(playload_len[0]).to_string());
  bit_string.append((bitset<8>(playload_len[1])).to_string());
  bit_string=bit_string.substr(9,7);
  len1=stoi(bit_string, nullptr, 2);
  len=len1;


  if(len1==126){
    char playload_len1[2];
    recv(client,playload_len1,2,0);
    len_flag+=2;
    bit_string="";
    bit_string.append(bitset<8>(playload_len1[0]).to_string());
    bit_string.append(bitset<8>(playload_len1[1]).to_string());
    len2=stoi(bit_string, nullptr, 2);
    len=len2;
  }
  if(len1==127){
    char playload_len2[4];
    recv(client,playload_len2,4,0);
    len_flag+=4;
    bit_string="";
    bit_string.append(bitset<8>(playload_len2[0]).to_string());
    bit_string.append(bitset<8>(playload_len2[1]).to_string());
    bit_string.append(bitset<8>(playload_len2[2]).to_string());
    bit_string.append(bitset<8>(playload_len2[3]).to_string());
    len3=stoi(bit_string, nullptr, 2);
    len=len3;
  }
  char masking_key[4];
  recv(client,masking_key,4,0);
  char encoded_data[len+1];
  recv(client,encoded_data,len,0);
  char decoded_data[len+1];
  int i=0;
  for(i=0;i<len;i++){
    decoded_data[i]=encoded_data[i]^masking_key[i%4];
  }
  decoded_data[i]='\0';
  return decoded_data;
}


string encode(string msg){
    int payload_len=msg.length()+1;
    string decoded_msg="";
    int len;
    char c=bitset<8>("10000001").to_ulong();
    decoded_msg+=c;
    if(payload_len<126){
      c=payload_len;
      decoded_msg+=c;
    }else{
      if(payload_len<=65535){
        //code here to handle msg with len <=65535
      }else{
        //code here to handle msg more len
      }
    }
    decoded_msg+=msg;
    return decoded_msg;
}
