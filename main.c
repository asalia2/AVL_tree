#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define size 6113

//AVL node
struct node{
 char word[50];
 char synonym[50];
 char antonym[50];
 struct String* meaning;//linked list of meaning
 struct node* left_child;
 struct node* right_child;
 int deleted;//if 0 not deleted
 int Height;
};

struct node_hash{
 char word[50];
 char synonym[50];
 char antonym[50];
 struct String* meaning;//linked list of meaning

};

//meaning node
struct String{
    char meaning[50];
    struct String* Next;
};
static struct node* tree;
static struct node* hash_arr[size];
//define functions:

int minu();

struct node* MakeEmpty(struct node* root);
int Height(struct node* root);
int max(int a, int b);
struct node* Right_single_rotation(struct node* root);
struct node* Left_Single_rotation(struct node* root);
struct node* Left_right_double_rotation(struct node* root);
struct node* Right_left_double_rotation(struct node* root);
struct node* Creat_node(char word[50],char synonym[50],char antonym[50],struct String* meaning);
struct node* Insert(struct node* root,char word[50],char synonym[50],char antonym[50],struct String* meaning );
struct node* Find(struct node* root,char word[50]);
struct node* deletion(struct node* root,char word[50]);
struct String* addNode(struct String* head,char meaning[50]);
struct String* createNode();
struct String* delete_List(struct String* head_ref);
void read_from_file();
void Insert_from_user();
struct node* Find_with_letter(struct node* root,char letter[2]);
void Print_InOrder_letter(struct node* root,char letter[2]);
void list_with_letter();
void delet_word();
void delete_with_letter();
void delete_InOrder_letter(struct node* root,char letter[2]);
void Print_in_file_InOrder( struct node* t,FILE * fp);

//hash:
int hash_menu(struct node_hash* hash_arr[]);
void return_into_file_hash(struct node_hash* hash_arr[]);
void read_hash(struct node_hash* hash_arr[]);
int Hash(struct node_hash* hash_arr[],int table_size,char *word);
void delet_hash(struct node_hash* hash_arr[],int table_size);
int search_hash(struct node_hash* hash_arr[]);
void insert_into_hash_table(struct node_hash* hash_arr[]);
int find_index_hash(struct node_hash* hash_arr[],int table_size,char word[]);
//====
void Print_all_info( struct node* t);


int main(){

    tree = MakeEmpty( NULL );
    struct String* k=NULL;
    int choice=0,ch=0;
    struct node_hash* hash_arr[size];
    for(int j=0;j<size;j++)
            hash_arr[j]=NULL;

     printf("\n======= Welcome ========\n");
    do{
        choice= minu();
        switch(choice){
        case 1://read data from the file
            read_from_file();
            break;
        case 2://Insert new word from user
            Insert_from_user();
            break;
        case 3://Find a word
            Find_and_update();
            break;
        case 4:// List the word in the dictionary with their associated meanings,synonym and antonyms
            Print_all_info(tree);

            break;
        case 5://List all synonym and antonyms of a given word
            list_syn_ant();
            break;
        case 6://List all words that start with the same first letter
            list_with_letter();
            break;
        case 7://Delete a word from the dictionary
            delet_word();
            break;
        case 8://Delete all words that start with a specific letter
            delete_with_letter();
            break;
        case 9://Save all words in file Dictionary.data
            save_all_in_file();


            read_hash( hash_arr);

            break;
        case 10:
            do{
                ch=hash_menu(hash_arr);

            }while(ch!=8);
            break;
        case 11://Exit
             printf(" Thank you ...\n");
            break;

         default:
            printf("The number you entered dose not exist!!!\n ");
            break;

        }

    }while(choice!=11);

    return 0;
}

// Functions:

int minu(){
    char in[2];
    int choice=1;
    printf("----------------------------\n");
    printf("1.To read the words from the file \n");
    printf("2.To Insert new word from user\n");
    printf("3.To Find a word\n");
    printf("4.To List the word in the dictionary with their associated meanings,synonym and antonyms\n");
    printf("5.To List all synonym and antonyms of a given word \n");
    printf("6.To List all words that start with the same first letter\n");//don
    printf("7.To Delete a word from the dictionary\n");//don
    printf("8.To Delete all words that start with a specific letter \n");//don
    printf("9.To Save all words in file Dictionary.data \n");
    printf("10.To show hash list \n");
    printf("11.To Exit \n");
    printf("===================================\n");
    printf("pleas chose one of option \n");
    scanf("%s",&in);
    choice=atoi(in);
    printf("\n");
    return choice;
}

void Print_all_info( struct node* t){
    if( t != NULL){

        Print_all_info( t->left_child );
        if(t->deleted==0){
            printf(" Word: %s  ", t->word);
            printf(" Synonym: %s  ",t->synonym);
            printf(" Antonym: %s  ",t->antonym);
            printf(" Meaning: ");
            struct String* ptr=t->meaning;
            if(t->meaning==NULL);
            else{
                while(ptr!=NULL){
                    printf(" %s\n",ptr->meaning );
                    ptr=ptr->Next;
                }
            }

             printf("\n");
        }

        Print_all_info( t->right_child );
    }
}

// Hash functions:

int hash_menu(struct node_hash* hash_arr[]){

    char in[2];
    int choice=1;

    printf("===   Hash List   =====\n");
    printf("=======================\n");
    printf(" 1.To Print hashed table \n");
    printf(" 2.To Print out table size\n");
    printf(" 3.To Print out hash function\n");
    printf(" 4.To Insert a new record into the hash table\n");
    printf(" 5.To Search for a specific word\n");
    printf(" 6.To Delete a specific record\n");
    printf(" 7.To Save hash table back to file\n");
    printf(" 8.To return back to previous list \n");
    //printf(" 9.To Exit \n");

    printf("pleas chose one of option \n");
    scanf("%s",&in);
    choice=atoi(in);
    printf("\n");

    switch(choice){
    case 1:

        for(int i=0;i<size;i++){
            if(hash_arr[i]==NULL)
                printf("%d:-----\n",i);
            else
               printf("%d: %s \n",i,hash_arr[i]->word);
        }
    break;
    case 2:
        printf(" Table size: %d\n\n",size);

    break;
    case 3:
        printf("\n Hash function:\n\n");
        printf(" h(x)= h1 + h2\n");
        printf(" while : \n");
        printf("         h1= (numb << 3)+ (*word)      numb= 0,1,2,3,...\n");
        printf("                                       word ++\n");
        printf("         h2= k * h1                     0<= k <= size \n\n");

    break;
    case 4: // Insert into hash table:
        insert_into_hash_table(hash_arr);

    break;
    case 5://search:
        search_hash(hash_arr);
    break;
    case 6://Delete:
        delet_hash(hash_arr,size);
    break;
    case 7://return into file:

    return_into_file_hash(hash_arr);

    break;
    case 8:

    break;
    default:
        printf("The number you entered dose not exist!!!\n ");
    break;

    }
    printf("\n----------------\n");
    return choice;
}

void return_into_file_hash(struct node_hash* hash_arr[]){
    FILE * fp;
    fp = fopen ("Dictionary.data","w");
    struct String* ptr;
    for(int i=0;i<size;i++){
        if(hash_arr[i]==NULL);
        else{
            fprintf(fp,"%s: ",hash_arr[i]->word);
            // to print meanings:

            if(hash_arr[i]->meaning==NULL);
            else{
                ptr=hash_arr[i]->meaning;
                while(ptr!=NULL){
                    fprintf(fp," %s ",ptr->meaning );

                    if(ptr->Next!=NULL)
                        fprintf(fp,",");
                    ptr=ptr->Next;
                }
            }

            fprintf(fp," / ");
            fprintf(fp," %s * %s \n",hash_arr[i]->synonym,hash_arr[i]->antonym);
        }
    }
      fclose (fp);

      printf(" Saved successfully \n");
}

void read_hash(struct node_hash* hash_arr[]){
    FILE *fop_hash;

    fop_hash = fopen("Dictionary.data", "r");
    if (fop_hash == NULL){
        perror("Error while opening the file.\n");
       return 0;
     }

     while (!feof(fop_hash)){ // char word[50],char synonym[50],char antonym[50],struct String* meaning
        int hash_valu=0;
        char line[200],word[50],synonym[50],antonym[50],meaning[200];
        char* token;
        struct String* Ptr_meaning=NULL;
        //get info from file
       if(fgets(line,200,fop_hash)!=NULL&&*line!='\n'){

            strcpy(word,strtok (line,":"));
            strcpy(meaning,strtok (NULL,"/"));
            strcpy(synonym,strtok (NULL,"*"));
            strcpy(antonym,strtok (NULL,"\n"));

        // add meanings of the word into linked list
            token = strtok(meaning, ",");

            while (token != NULL) {
                Ptr_meaning=addNode(Ptr_meaning,token);
                token = strtok(NULL, ",");
            }
            trimleading(word);
            trim_eading(word);

            struct node* root_hash= Creat_node(word,synonym,antonym,Ptr_meaning);
            hash_valu= Hash(hash_arr,size,word); // change size ********

            hash_arr[hash_valu]=root_hash;

        }
   }
   printf(" Read from file successfully!! \n");
   fclose(fop_hash);

}

int Hash(struct node_hash* hash_arr[],int table_size,char *word){
    int numb=0,hash_valu=0;
    while(*word!='\0' ){
        numb =(numb<<3)+(*word);
        word++;
    }
    while(numb<0)
        numb+=table_size;

    hash_valu=numb%table_size; // h1

    for(int k=0;k<=size;k++){
        // hash_valu=(hash_valu+k)%size;
        hash_valu=(hash_valu+k*hash_valu)%size; //(h1+h2)%size
        if(hash_arr[hash_valu]==NULL){
            break;
        }
    }

    return hash_valu;
}

void insert_into_hash_table(struct node_hash* hash_arr[]){
    printf("");
       char word[50],synonym[50],antonym[50],meaning[200],in[2];
    char* token;
    struct String* Ptr_meaning=NULL;
    int numb=0,hash_valu=0;
    fflush(stdin);
    printf("Enter the word :");
    gets(word);
    trimleading(word);
    fflush(stdin);
    printf("Enter the synonym of the word :");
    gets(synonym);
    fflush(stdin);
    printf("Enter the antonym of the word :");
    gets(antonym);
    fflush(stdin);
    printf("Enter the # of meaning you need to insert:(up to three meanings)");
    gets(in);
    numb=atoi(in);
    for(int i=1;i<=numb;i++){
        fflush(stdin);
        printf("\nEnter the meaning #%d : ",i);
        token =gets(meaning);
        Ptr_meaning=addNode(Ptr_meaning,token);
    }

    trimleading(word);
    trim_eading(word);

    struct node* root_hash= Creat_node(word,synonym,antonym,Ptr_meaning);
    hash_valu= Hash(hash_arr,size,word); // change size ********

    hash_arr[hash_valu]=root_hash;
    printf(" Done!!!\n");

}

void delet_hash(struct node_hash* hash_arr[],int table_size){

    int index=search_hash(hash_arr);

    if (index!=-1){// to delete the word
       delete_List(hash_arr[index]->meaning);
        hash_arr[index]=NULL;
    printf("\n   ==========================\n");
    printf("   =  Deleted successfully! =\n");
    printf("   ==========================\n\n");
    }
}

int search_hash(struct node_hash* hash_arr[]){

    struct String* ptr=NULL;
    char word[50];
    int index=0;

    fflush(stdin);
    printf("Enter the word you looking for: ");
    gets(word);

    trimleading(word);
    trim_eading(word);

    index=find_index_hash(hash_arr,size,word);
    if(hash_arr[index]==NULL||index==-1){
        printf("\n\n  ====================\n");
        printf("  =   Not founded!!  =\n");
        printf("  ====================\n\n");
         return -1;
    }

    printf("\n Word: %s\n",hash_arr[index]->word);
        //
    if(hash_arr[index]->meaning ==NULL);
    else{
        printf(" Meanings:\n");
        ptr=hash_arr[index]->meaning;
        while(ptr!=NULL){
            printf(" %s \n",ptr->meaning );

            ptr=ptr->Next;
        }
    }

    printf(" Synonym: %s\n",hash_arr[index]->synonym);
    printf(" Antonym: %s\n",hash_arr[index]->antonym);


    return index;
}

int find_index_hash(struct node_hash* hash_arr[],int table_size,char word[]){
     int numb=0,hash_valu=0,i=0;
    while(word[i]!='\0' ){
        numb =(numb<<3)+(word[i]);
        i++;
    }
    while(numb<0)
        numb+=table_size;

    hash_valu=numb%table_size; // h1

    for(int k=0;k<=size;k++){
        hash_valu=(hash_valu+k*hash_valu)%size; //(h1+h2)%size
        if(hash_arr[hash_valu]==NULL){
            return -1;// if the index i visited empty
        }

        else if(strcasecmp(word,hash_arr[hash_valu]->word)==0){
            return hash_valu;
        }
    }

    return hash_valu;
}


/* to List words start with letter :
 First we need to find the root start with the same letter
 then print in order start from this root
 instead of looking at all the tree
*/
void list_with_letter(){
    char letter[2];
    fflush(stdin);
    printf(" Enter the letter you looking for:");
    gets(letter);
    trimleading(letter);
    struct node* temp=Find_with_letter(tree,letter);
    Print_InOrder_letter(temp,letter);
}

void Print_InOrder_letter(struct node* root,char letter[2]){
    if( root != NULL){
       Print_InOrder_letter( root->left_child ,letter);
        if(root->deleted==0&&(strncasecmp(letter,root->word,1)==0))
            printf("%s\n", root->word);
        Print_InOrder_letter( root->right_child ,letter);
    }

}

struct node* Find_with_letter(struct node* root,char letter[2]){
    if(root== NULL){
      //  printf("\n NOT FOUND !\n");
       return NULL;
    }
    else if(strncasecmp(letter,root->word,1)<0)
        return Find_with_letter(root->left_child,letter);
    else if(strncasecmp(letter,root->word,1)>0)
        return Find_with_letter(root->right_child,letter);
    else
        return root;
}

/*to delete a word from dictionary
 node->deleted become equal 1
*/
void delet_word(){
    struct node* temp;
    char word[50];
    fflush(stdin);
    printf("Enter the word you looking for: ");
    gets(word);
    temp=deletion(tree,word);
    if (temp==NULL)
          printf("\n NOT FOUND !\n");
    else
        printf(" Deleted Successfully \n");

}

struct node* deletion(struct node* root,char word[50]){
    struct node* temp = Find(root,word);

    if (temp==NULL)
        return NULL;
    else if(temp->deleted==0){
         temp->deleted=1;
         return NULL;
    }
    return temp;
}

/* to delete all the word start with given letter
first we find the first root that start with the given letter
then we delete
*/
void delete_with_letter(){
    char letter[2];
    fflush(stdin);
    printf(" Enter the letter you looking for:");
    gets(letter);
    trimleading(letter);
    struct node* temp=Find_with_letter(tree,letter);

    if(temp==NULL)
          printf("\n NOT FOUND !\n");
    else
        printf(" Deleted Successfully \n ");
    delete_InOrder_letter(temp,letter);


}

void delete_InOrder_letter(struct node* root,char letter[2]){
    if( root != NULL){
       delete_InOrder_letter( root->left_child ,letter);
        if(root->deleted==0&&(strncasecmp(letter,root->word,1)==0))
           root->deleted=1;
        delete_InOrder_letter( root->right_child ,letter);
    }

}

//=========
void save_all_in_file(){

    struct node* n=tree;
    FILE * fp;
    fp = fopen ("Dictionary.data","w");
    Print_in_file_InOrder(tree,fp);
    fclose (fp);
}
//====
void Print_in_file_InOrder( struct node* t,FILE * fp){
    struct String* ptr;
    if( t != NULL){
       Print_in_file_InOrder( t->left_child ,fp);//old: advanced in age, aged, antique / ancient * new
        if(t->deleted==0){// change:
              fprintf(fp,"%s: ",t->word);
                // to print meanings:

                if(t->meaning==NULL);
                else{
                    ptr=t->meaning;
                    while(ptr!=NULL){
                        fprintf(fp," %s ",ptr->meaning );

                        if(ptr->Next!=NULL)
                            fprintf(fp,",");

                          ptr=ptr->Next;
                    }
                }
                //***
                    fprintf(fp," / ");
                fprintf(fp," %s * %s \n",t->synonym,t->antonym);

        }
        Print_in_file_InOrder( t->right_child,fp );

    }
}
//======
void list_syn_ant(){
    char word[50];
    struct node*temp;
    fflush(stdin);
    printf("Enter the word you looking for: ");
    gets(word);
    temp=Find(tree,word);
    if(temp==NULL){
        printf("Not found!\n");
        return;
    }
    else if(temp->deleted==1){
        printf("Not found!\n");
        return;
    }
    printf("The word founded:\n");
    printf("synonym:%s\n",temp->synonym);
    printf("antonym:%s\n",temp->antonym);
}

void Find_and_update(){
    char word[50],synonym[50],antonym[50],meaning[50],in1[2],in2[2];
   struct node* temp;
    int numb1,numb2;
    char* token;
    fflush(stdin);
    printf("Enter the word you looking for: ");
    gets(word);
    temp=Find(tree,word);
    if(temp==NULL){
        printf("Not found!\n");
        return;
    }
    else if(temp->deleted==1){
        printf("Not found!\n");
        return;
    }
    printf("The word founded:\n");
    printf("Word:%s\n", temp->word);
    printf("synonym:%s\n",temp->synonym);
    printf("antonym:%s\n",temp->antonym);
    printf("meaning:\n");

    struct String* ptr=temp->meaning;
    if(temp->meaning==NULL);
    else{
        while(ptr!=NULL){
            printf(" %s\n",ptr->meaning );
            ptr=ptr->Next;
        }
    }

    printf("-----------------\n");
    fflush(stdin);
    printf("If you want to update word's information print ( 1 )\n");
    printf("else press any key\n");
    gets(in1);
    numb1=atoi(in1);
    if(numb1==1){ // update info:

        temp->meaning=delete_List(temp->meaning);

        fflush(stdin);
        printf("Enter the new synonym of the word :");
        gets(synonym);
        strcpy(temp->synonym,synonym);
        fflush(stdin);
        printf("Enter the new antonym of the word :");
        gets(antonym);
        strcpy(temp->antonym,antonym);
        fflush(stdin);
        printf("Enter the # of meaning you need to insert:(up to three meanings)");
        gets(in2);
        numb2=atoi(in2);
        for(int i=1;i<=numb2;i++){//to insert new meaning
            fflush(stdin);
            printf("\nEnter the meaning #%d : ",i);
            token =gets(meaning);
            temp->meaning=addNode(temp->meaning,token);
        }
    }

}

void Insert_from_user(){
    char word[50],synonym[50],antonym[50],meaning[200],in[2];
    char* token;
    struct String* Ptr_meaning=NULL;
    int numb=0;
    fflush(stdin);
    printf("Enter the word :");
    gets(word);
    trimleading(word);
    fflush(stdin);
    printf("Enter the synonym of the word :");
    gets(synonym);
    fflush(stdin);
    printf("Enter the antonym of the word :");
    gets(antonym);
    fflush(stdin);
    printf("Enter the # of meaning you need to insert:(up to three meanings)");
    gets(in);
    numb=atoi(in);
    for(int i=1;i<=numb;i++){
        fflush(stdin);
        printf("\nEnter the meaning #%d : ",i);
        token =gets(meaning);
        Ptr_meaning=addNode(Ptr_meaning,token);
    }
        tree = Insert(tree,word,synonym,antonym,Ptr_meaning);

}

void read_from_file(){
    FILE *fop;

    fop = fopen("Words.txt", "r");
    if (fop == NULL){
        perror("Error while opening the file.\n");
       return 0;
     }


     while (!feof(fop)){ // char word[50],char synonym[50],char antonym[50],struct String* meaning
        char line[200],word[50],synonym[50],antonym[50],meaning[200];
        char* token;
        struct String* Ptr_meaning=NULL;
        //get info from file
        fgets(line,200,fop);;
        strcpy(word,strtok (line,":"));
        strcpy(meaning,strtok (NULL,"/"));
        strcpy(synonym,strtok (NULL,"*"));
        strcpy(antonym,strtok (NULL,"\n"));
        // add meanings of the word to linked list
        token = strtok(meaning, ",");
        while (token != NULL) {
            Ptr_meaning=addNode(Ptr_meaning,token);
            token = strtok(NULL, ",");
        }
        trimleading(word);
        tree = Insert(tree,word,synonym,antonym,Ptr_meaning);



   }
   printf(" Read from file successfully!! \n");
   fclose(fop);
}


struct node* Find(struct node* root,char word[50]){
    if(root== NULL){
      //  printf("\n root is null\n");
       return NULL;
    }
    else if(strcasecmp(word,root->word)<0)
        return Find(root->left_child,word);
    else if(strcasecmp(word,root->word)>0)
        return Find(root->right_child,word);
    else
        return root;
}

struct node* Creat_node(char word[50],char synonym[50],char antonym[50],struct String* meaning){
   struct node* root = (struct node*)malloc(sizeof( struct node));
        if( root == NULL )
            printf( "Out of space!!!" );
        else{

            strcpy(root->word,word);
            strcpy(root->synonym,synonym);
            strcpy(root->antonym,antonym);
            root->meaning=meaning;
            root->Height = 0;
            root->deleted=0;
            root->left_child = root->right_child = NULL;
        }
    return root;
};

struct node* Insert(struct node* root,char word[50],char synonym[50],char antonym[50],struct String* meaning ){

    if( root == NULL )
        root= Creat_node(word,synonym,antonym,meaning);

    else if(strcasecmp(word,root->word)<0){
        root->left_child =Insert(root->left_child,word,synonym,antonym,meaning);
        if( Height(root->left_child)- Height(root->right_child)==2)
            if(strcasecmp(word,root->left_child->word)<0)
                root = Right_single_rotation( root );
            else
                root = Left_right_double_rotation( root );
    }
    else if(strcasecmp(word,root->word)> 0){
        root->right_child = Insert(root->right_child,word,synonym,antonym,meaning);
        if( Height( root->right_child )- Height(root->left_child)== 2 )
            if(strcasecmp(word,root->word)>0)
                root = Left_Single_rotation( root );
            else
                root = Right_left_double_rotation( root );
    }
    else if(strcasecmp(word,root->word)== 0)
        root->deleted=0;
    root->Height = max( Height( root->left_child ), Height( root->right_child ) ) + 1;
    return root;
}

struct node* Right_single_rotation(struct node* root){
    struct node* temp;
    temp = root->left_child;
    root->left_child = temp->right_child;
    temp->right_child = root;
    //Height
    root->Height= max(Height(root->left_child),Height(root->right_child))+1;
    temp->Height= max(Height(temp->left_child),Height(temp->right_child))+1;

    return temp;
}

struct node* Left_Single_rotation(struct node* root){
    struct node* temp;
    temp= root->right_child;
    root->right_child = temp->left_child;
    temp->left_child = root;
    //Height
    root->Height= max(Height(root->left_child),Height(root->right_child))+1;
    temp->Height= max(Height(temp->right_child),Height(temp->right_child))+1;

    return temp;
}

struct node* Left_right_double_rotation(struct node* root){

    root->left_child = Left_Single_rotation( root->left_child );
    return Right_single_rotation(root);
}

struct node* Right_left_double_rotation(struct node* root){

    root->right_child = Right_single_rotation(root->right_child);
    return Left_Single_rotation(root);
}

struct node* MakeEmpty(struct node* root){
    if(root!= NULL){
        MakeEmpty(root->left_child);
        MakeEmpty(root->right_child);
        free(root);
    }
    return NULL;
}

int Height(struct node* root){
    if(root==NULL)
        return -1;
    else
        return root->Height;
}

int max(int a, int b){
if(a > b)
  return a;
return b;
}


// linked list functions:
struct String* createNode(){
    struct String* temp;
    temp = (struct String*)malloc(sizeof(struct String));
    temp->Next = NULL;
    return temp;
}

// add node to string list (list of meaning)
struct String* addNode(struct String* head,char meaning[50]){
    struct String* temp,*p;
    temp = createNode();
    strcpy(temp->meaning,meaning);
    if(head == NULL){
        head = temp;
    }
    else{
        p = head;
        while(p->Next != NULL){
            p = p->Next;
        }
        p->Next = temp;
    }
    return head;
}

// To delete linked list of String
struct String* delete_List(struct String* head_ref){
   struct String* current = head_ref;
   struct String* next;

   while (current != NULL){
       next = current->Next;
       free(current);
       current = next;
   }
   head_ref = NULL;
   return NULL;
}

// trim the word
void trimleading(char *str){
	int i,j;
	for(i=0;str[i]==' '||str[i]=='\t';i++);
	for(j=0;str[i];i++){
		str[j++]=str[i];
	}
	str[j]='\0';
}

void trim_eading(char *str){
    int k=strlen(str);
	 char* back;

    if(k == 0)
        return ;

    back = str + k;//point to last endix
    while(isspace(*--back));
    *(back+1) = '\0';
}

