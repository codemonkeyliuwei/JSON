//reference:
//http://noalgo.info/639.html
//http://my.oschina.net/u/2255341/blog/543508
//http://blog.csdn.net/azhou_hui/article/details/8333728

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdint.h>
#include "cJSON.h"  //��Ҫ�Ѹ�ͷ�ļ����ں������  ������Ҳ���size_t

//����JSON
void parse_json(const char *filename)
{
    printf("----------------parse json start------------------\n");

    //���ļ��ж�ȡҪ������JSON����
    FILE *fp = fopen(filename, "rb");
    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *data = (char*)malloc(len + 1);
    data[len] = '\0';
    fread(data, 1, len, fp);
    fclose(fp);
    //printf("%s", data);
    //����JSON����
    cJSON *root_json = cJSON_Parse(data);    //���ַ���������json�ṹ��
    if (NULL == root_json)
    {
        printf("error:%s\n", cJSON_GetErrorPtr());
        cJSON_Delete(root_json);
        return;
    }
    //"name":"test"
    cJSON *name_json = cJSON_GetObjectItem(root_json, "name");
    if (name_json != NULL)
    {
        char *name = cJSON_Print(name_json);    //��JSON�ṹ���ӡ���ַ����� ��Ҫ�Լ��ͷ�
        printf("name:%s\n", name);
        free(name);
    }
    //"data":"..."
    //id: int
    cJSON *data_json = cJSON_GetObjectItem(root_json, "data");
    int id = cJSON_GetObjectItem(data_json, "id")->valueint;
    printf("id:%d\n", id);
    //username: string
    char *username = cJSON_Print(cJSON_GetObjectItem(data_json, "username"));
    printf("username:%s\n", username);
    free(username);
    //userpass: string
    char *userpass = cJSON_Print(cJSON_GetObjectItem(data_json, "userpass"));
    printf("userpass:%s\n", userpass);
    free(userpass);
    //version: float
    //char *version = cJSON_Print(cJSON_GetObjectItem(data_json, "version"));
    float version = cJSON_GetObjectItem(data_json, "version")->valuedouble;
    printf("version:%f\n", version);
    //free(version);
    free(data);

    //array
    cJSON* array = cJSON_GetObjectItem(data_json, "array");
    if (array)
    {
        int size = cJSON_GetArraySize(array);
        printf("array size=%d\n", size);
        for (int i = 0; i < size; ++i)
        {
            cJSON* pItem = cJSON_GetArrayItem(array, i);
            char* item = pItem->valuestring;
            printf("item-%d=%s\n", i, item);
            free(item);
        }
    }
    
    printf("----------------parse json end-----------------\n");
}

//����JSON
void create_json()
{
    printf("----------------create json start-----------------------------\n");
    //��JSON
    cJSON *root_json = cJSON_CreateObject();
    cJSON_AddItemToObject(root_json, "name", cJSON_CreateString("CRATE TEST"));
    cJSON *data_json = cJSON_CreateObject();
    cJSON_AddItemToObject(root_json, "data", data_json);
    //��ӵ���һ�ַ�ʽ:cJSON_AddNumberToObject(data_json, "id", 1);ͨ��Դ�뷢�ֽ����Ƕ�cJSON_AddItemToObject��define
    cJSON_AddItemToObject(data_json, "id", cJSON_CreateNumber(2));
    //��ӵ���һ�ַ�ʽ:cJSON_AddStringToObject(data_json, "username", "ddp");
    cJSON_AddItemToObject(data_json, "username", cJSON_CreateString("ddp"));
    cJSON_AddItemToObject(data_json, "userpass", cJSON_CreateString("123456"));
    cJSON_AddItemToObject(data_json, "version", cJSON_CreateString("1.0"));
    //��ӡJSON
    char *out = cJSON_Print(root_json);
    printf("%s\n", out);
    free(out);
    printf("----------------create json end-------------------------------\n");
}
int main()
{
    parse_json("test.json");
    create_json();
    return 0;
}