#include <iostream>
#include <dirent.h>
#include <stack>
#include <string>
#include <queue> 
#include <vector>
#include <algorithm>    // std::reverse

#include "Node.hpp"

using namespace std;

void treeTraversalParent(Node* node) {
    if (node == NULL ) 
        return; 
    vector<string> path;
    path.push_back(node->getName());
    
    while ( node->getParent() != NULL) {
        //cout << "folder  name : " << node->getParent()->getName() << "/";
        path.push_back(node->getParent()->getName());
        node = node->getParent();
    }
    std::reverse(path.begin(),path.end());  
    for(int i = 0 ;i < path.size() -1 ; ++i){
        cout << path[i]; if(path[i] != "/") cout << "/";
    }
    cout << path[path.size() -1] << endl;
}

void treeTraversal(Node* node) {
    if (node == NULL) 
        return; 
    cout << "traversing" << endl;
    for (Node*  nodeEntry : *node->getList()) {
        if ( nodeEntry->getIsDir() ) {
            cout << "folder  name : " << nodeEntry->getName() << endl;
            treeTraversal(nodeEntry);
            treeTraversalParent(nodeEntry);
        }
        else 
            cout << "file  name : " << nodeEntry->getName() << endl;
        
   
    }
}

void treeTraversalSearch(Node* node , string pat ) {
    if (node == NULL) 
        return; 
    for (Node * nodeEntry : *node->getList()) {
        if (nodeEntry->getIsDir()) {
            //System.out.println("folder  name : " + nodeEntry.getName());
                if (nodeEntry->getName().find(pat) != std::string::npos) {
                    cout << "found folder  name : " << nodeEntry->getName() << " full path :" ;
                    treeTraversalParent(nodeEntry);
                }
            treeTraversalSearch(nodeEntry , pat);
        }
        else {
                if (nodeEntry->getName().find(pat) != std::string::npos) {
                    cout << "found file  name : " << nodeEntry->getName() << " full path :" ;
                    treeTraversalParent(nodeEntry );
                }
                    
        }
    }
}


void createDirNode(string dirname , Node * node){

    vector<Node*> *list= new vector<Node*>();
    node->setList(list);
    struct dirent *direntry = NULL;
    DIR *dir;
    /* Open the directory */
    if (!(dir = opendir(dirname.c_str())))
        return;
    while ((direntry = readdir(dir)) != NULL)
        {
            Node* childNode = new Node();
            childNode->setParent(node);

            string tempstring(direntry->d_name);
            if (direntry->d_type == 4) //if it is a directory not a file
            {
                
                if(( tempstring != "." && tempstring != "..")){
                    //dirQueue.push(dirname + "/"+ tempstring);
                    childNode->setIsDir(true);
                    childNode->setName(tempstring);
                    list->push_back(childNode);
                    createDirNode(dirname +  tempstring +"/",childNode);
                }
                    
            }
            else{
                childNode->setIsDir(false);
                childNode->setName(tempstring);
                list->push_back(childNode);
                //cout << dirname << "/" << tempstring << endl ;
            }
        } 
    /* close the directory */
		closedir(dir);
}

int main(int argc, char *argv[]) {

    DIR *dir;
	struct dirent *direntry = NULL;
	string dirnameRoot = "/";
    Node * root = new Node();
    root->setName(dirnameRoot);
    root->setIsDir(true); // assuming that u start with a folder not file, should check for this if u read from input
    createDirNode(dirnameRoot, root);

    string mystr;
    while(true){
        cout << "What's your search String? ";
        getline (cin, mystr);
        //treeTraversal(root);
        treeTraversalSearch(root, mystr);
    }

    // queue<string> dirQueue;
    // dirQueue.push(dirnameRoot);

    // while (!dirQueue.empty())
	// {
	// 	string dirname = dirQueue.front();
    //     dirQueue.pop();
	// 	/* Open the directory */
	// 	if (!(dir = opendir(dirname.c_str())))
	// 		continue;

	// 	while ((direntry = readdir(dir)) != NULL)
	// 		{
	// 		string tempstring(direntry->d_name);
	// 			if (direntry->d_type == 4) //if it is a directory not a file
	// 			{
	// 				if(( tempstring != "." && tempstring != ".."))
	// 					dirQueue.push(dirname + "/"+ tempstring);
	// 			}
	// 			else{
	// 				cout << dirname << "/" << tempstring << endl ;
	// 			}
	// 		}
	// 	/* close the directory */
	// 	closedir(dir);
	// }

    return 0;
}