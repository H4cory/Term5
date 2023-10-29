#include <iostream>
#include <stack>

using namespace std;

// class for the diffrent nodes
class cNodes
{
private:
    int link[100];
    int linkCounter = 0;
    //DELTE
    bool crawled = false;
    bool available = false;

public:
    // gets a link value
    void getLink(int temp)
    {
        link[linkCounter] = temp;
        linkCounter++;
    }

    // returns the number of links
    int returnLinkCounter()
    {
        return linkCounter;
    }

    // returns a link
    int returnLink(int temp)
    {
        return link[temp];
    }

//DELETE
    // switches nodes status to crawled
    void crawledT()
    {
        crawled = true;
    }

//DELETE
    // returns if Node is crawled
    // bool returnCrawled()
    // {
    //     return crawled;
    // }

    // switches Node status to availabel
    void availableT()
    {
        available = true;
    }

    // returns if the node is available
    bool returnAvailable()
    {
        return available;
    }

    //DELETE
    // displays links for debug purpose
    // void displayLinks()
    // {
    //     for (int i = 0; i < linkCounter; i++)
    //     {
    //         cout << link[i] << " | ";
    //     }
    // }
};

// get user input of nodes and links
void getUserInput(cNodes node[], int &numberOfNodes, int &numberOfLinks, int &firstNode)
{
    
    bool gate = true, accept = true;

    while(accept){
    // gets number of nodes and theyr links
    cout << "\nNumber of Nodes & Links: ";
    cin >> numberOfNodes;
    cin >> numberOfLinks;

    if(1<numberOfNodes&&numberOfNodes<=3000&&0<=numberOfLinks&&numberOfLinks<=4000000){
        accept = false;
    }
    else{
        cout<<"Out of range Input!\n";
    }
}

    // gets the links
    for (int i = 0, temp1 = 0, temp2 = 0; i < numberOfLinks; i++)
    {
        cout << "Link " << i + 1 << ": ";
        cin >> temp1;
        cin >> temp2;
        node[temp1].getLink(temp2);

        // idk if i need this
        node[temp2].getLink(temp1);

        // executes once and gets the index of the first node
        if (gate)
        {
            firstNode = temp1;
            gate = false;
        }
    }

}

// crawles a Node
void crawl(cNodes node[], int selectedNode, stack<int> &waiting)
{

    // start of crawl
    for (int i = 0, selectedLink = 0; i < node[selectedNode].returnLinkCounter(); i++)
    {
        // gets the a link value
        selectedLink = node[selectedNode].returnLink(i);

        // cheks if it is available
        if (node[selectedLink].returnAvailable())
        {
        }

        // if its not available, marks it as available
        // and puts it in a quee
        else
        {
            node[selectedLink].availableT();
            waiting.push(selectedLink);
        }
    }

//DELETE
    // marks the node as crawled
    node[selectedNode].crawledT();
}

//checks if nodes are connectet and if not, creates
//a link between the first node and the first 
//not connected node
void checkNodes(cNodes node[],int numberOfNodes, int firstNode, bool &gate){
    for (int i = 0; i < numberOfNodes; i++)
    {
        if(!node[i].returnAvailable()){
            node[firstNode].getLink(i);
            node[i].getLink(firstNode);
            gate = false;
            break;
        }
    }
    
}


int main()
{
    cNodes node[100];
    int selectedNode = 0, numberOfNodes = 0, numberOfLinks = 0, firstNode = 0, numberOfAddedLinks = 0;
    stack<int> waiting;
    bool gate = true;

    // gets user input 
    getUserInput(node,numberOfNodes,numberOfLinks,firstNode);
    //selects the index of the first node
    selectedNode = firstNode;

    // marks the first node as available
    node[selectedNode].availableT();

    while(true){
    //pushes the first node into the steck so its not empty
    waiting.push(firstNode);

    // crawls tru nodes
    do
    {

        crawl(node, selectedNode, waiting);
        selectedNode = waiting.top();
        waiting.pop();

    } while (!waiting.empty());

    //cheks if all nods are connected
    gate = true;
    checkNodes(node,numberOfNodes,firstNode, gate);

    //if all nodes are connected the cycle breaks
    if(gate){
        break;
    }

    //if there are disconnected nodes the cycle
    //continues and the number of added nodes
    //increases
    else{
        selectedNode = firstNode;
        numberOfAddedLinks++;
    }

    }

    //return to the user the number of added links
    cout<<"\nNumber of added links: "<<numberOfAddedLinks;


    //DELETE
    //display the tablic format of the graph
    //  for (int i = 0; i <= numberOfNodes; i++)
    //  {
    //      cout<<endl<<"Links "<<i<< ": ";
    //      node[i].displayLinks();
    //      cout<<endl;
    //  }

    return 0;
}