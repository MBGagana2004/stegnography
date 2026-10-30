/*name: MB Gagana
  date: 5/5/2026
  project no: 2
  project name: lsb image stegnography
  batch no: int26001B(005)
  description: this project implements lsb image stegnography to securely hide confidential data inside a BMP image without
  visibly altering it. the least significant bits of image pixels are modified to embed secret information such as text file.
  it supports both encoding(hiding data) and decoding (retrieving data) operations. A magic string is used for authentication
  during extraction. this ensures secure and undetectable communition of sensitive data.*/
#include<stdio.h>
#include"encode.h"
#include"types.h"
#include<string.h>
#include"decode.h"
#include"common.h"

int main(int argc,char *argv[]){
    //check if no arguments are passed
    if(argc==1){
        printf(RED "Pass correct argument\n" RESET);
        printf(YELLOW "./a.out -e beautiful.bmp secret.txt stego.bmp --> for encoding\n" RESET);
        printf(YELLOW "./a.out -d stego.bmp --> for decoding\n" RESET);
        return e_failure;
    }
    //check if user selected encoding operation
    if(check_operation_type(argc,argv)==e_encode){
    //inform user encoding is selected
        printf(GREEN "you choosen encodeing\n" RESET);
    //validate minimum required arguments for encoding 
          if(argc < 4){
          printf(RED "ERROR: Insufficient arguments for encoding\n" RESET);
          printf(YELLOW "Usage: ./a.out -e <input.bmp> <secret.txt> <output.bmp>\n" RESET);
        return e_failure;
}
    //structure to hold encoding information
        EncodeInfo encInfo;
    //read and validate encoding arguments
        if(read_and_validate_encode_args(argc,argv,&encInfo)==e_success){
        
    
            printf(GREEN "reading  and validate successful\n" RESET);
    //take magic string input from user
            printf(BLUE "enter magic string:" RESET);
            scanf(" %[^\n]",encInfo.magic);
    //perform encoding process
            if(do_encoding(&encInfo)==e_success){
                printf(GREEN "encoding is successfully done\n" RESET);

            }else{
    
                printf(RED "Encoding is unsuccessful \n" RESET);
                return e_failure;
            }

        }else{
    //arguments validation failed
            printf(RED "Read and validate is Not successful\n" RESET);
            return e_failure;
        }
    //close all opened files after encoding
        fclose(encInfo.fptr_src_image);
        fclose(encInfo.fptr_secret);
        fclose(encInfo.fptr_stego_image);

    }
    //check if user selected decoding operation
    else if(check_operation_type(argc,argv)==e_decode){
    //inform user decoding is selected
        printf(GREEN "you choosen decoding\n" RESET);
    //validate minimum required arguments for decoding
        if(argc < 3){
          printf(RED "ERROR: Insufficient arguments for decoding\n" RESET);
           printf(YELLOW "Usage: ./a.out -e <input.bmp> ----> decoding\n" RESET);
          return e_failure;
}
    //structure to hold decoding information
        DecodeInfo decInfo;
    //read and validate decoding arguments
        if(read_and_validate_decode_args(argc,argv,&decInfo)==e_success){

            printf(GREEN "reading and validating is successfull\n" RESET);
    //take magic string input from user
            printf(BLUE "enter magic string:" RESET);
            scanf(" %[^\n]",decInfo.magic);
    //perform decoding process
            if(do_decoding(&decInfo)==e_success){
                printf(GREEN "decoding successful\n" RESET);
            }else{
                printf(RED "decoding unsuccessful\n" RESET);
                return e_failure;
            }

        }else{
    //argument validation failed
            printf(RED "reading and validating is unsuccessful\n" RESET);
            return e_failure;
        }

    }
    //if invalid option is provided

    else{
        printf(RED "Pass correct argument\n" RESET);
        printf(YELLOW "./a.out -e beautiful.bmp secret.txt stego.bmp --> for encoding\n" RESET);
        printf(YELLOW "./a.out -d stego.bmp --> for decoding\n" RESET);
        return e_failure;
    }

    return e_success;
}
/*
 *function: check_operation_type
 *purpose: determine operation type from command-line argument
*         -"-e"-> encoding
*         -"-d"-> decoding
*         - otherwise -> unsupported
*/

OperationType check_operation_type(int argc,char *argv[]){
//check for encoding option
    if((strcmp(argv[1],"-e"))==0){
        return e_encode;
    }
//check for decoding option
    else if(strcmp(argv[1],"-d")==0){
        return e_decode;
    }
//unsupported option
    else
        return e_unsupported;
}