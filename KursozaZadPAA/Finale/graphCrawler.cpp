/*
--Opisanie
        Celta na softuera e pri wywejdane na graf, programata da izchisli dali imame dostyp
    do wsichki wyzli i ako nqmame, da izwede kolko rebra trqbwa da se dobawqt. Programata
    dopuska che rebrata sa dwuposochni i nqma tejest.
        Dannite se wywejdat kato na pyrwiq red ot standartniqt whod se wywejda 2 chisla,
    pyrwoto za broqt wyzli, a wtoroto za broqt rebra. Sled izchislenie programata izwejda
    1 chislo, koeto otgowarq na broqt rebra koito trqbwa da bydat dobaweni.
        Algotirymyt na rabota na osftuera e sledniqt. Sled wywejdaneto na dannite programata
    gi zapazwa w klas ot obekti, koito otgowarqt na razlichnite wyzli. Izbira se pyrwiqt wyzel,
    markira se kato poseten i se prosledqwat negowite rebra. Namerenite wyzli se markirat kato
    dostypni i se slagat w opashka za da bydat poseteni. Cikylyt spira kato wsichki dostypni
    wyzli bydat poseteni. Sledwashtoto neshto koeto programata prawi e da proweri dali wsichki
    wyzli sa poseteni, ako nameri neposeteni, programata syzdawa rebro mejdu pyrwiqt wyweden wyzel
    i pyrwiqt nameren neposeten wyzel. Pyrwiqt wyweden wyzel se slaga w opashka za poseshteniq i se
    prowerq otnowo.
        Programata powtarq tezi 2 cikyla dokato wsichki wyzli stanat dostypni. Togawa tq spira i
    izwejda na ekrana broqt dobaweni wryzki.

    *W programata wyzlite se narichat "Nodes", a rebrata "Links"

--Promenlivi
   -cNodes             - Class zapiswasht swoistwata na wyzlite
   -node               - cNodes - Obekt wyzel
   -link[]             - int    - Zapazwa stoinostite na rebrata
   -linkCounter        - int    - Zapazwa broqt na rebrata wyw wyzel
   -available          - bool   - Zapazwa dali programata ima dostyp do wyzela

   -temp               -   *    - Operatiwna promenliwa (temporary)
   -gate               - bool   - Operatiwna promenliwa (Logic Gate)

   -numberOfNodes      - int    - Zapazwa broqt na wywedenite wyzlite
   -numberOfLinks      - int    - Zapazwa broqt na wywedenite rebrat
   -numberOfAddedLinks - int    - Zapazwa broqt na dobawenite rebra
   -firstNode          - int    - Zapazwa indexa na pyrwiqt wyzel
   -selectedNode       - int    - Zapazwa indexa na izbraniqt wyzel
   -selectedLink       - int    - Zapazwa indexa na izbrano rebro
   -waiting            - stack  - Zapazwa indexi na wyzli koito trqbwa da bydat obhodeni

--Footer

Autor: KK
Date : 28.10.2023                          Last Modified: 29.10.2023
*/

#include <iostream>
#include <stack>

using namespace std;

// class for the diffrent nodes
class cNodes
{
private:
    int* link = new int[4000000];
    int linkCounter = 0;
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
};

// get user input of nodes and links
void getUserInput(cNodes node[], int &numberOfNodes, int &numberOfLinks, int &firstNode)
{

    bool gate = true;

    // gets number of nodes and theyr links
    // checks for the required input
    while (gate)
    {

        cin >> numberOfNodes;
        cin >> numberOfLinks;

        if (1 < numberOfNodes && numberOfNodes <= 3000 && 0 <= numberOfLinks && numberOfLinks <= 4000000)
        {
            gate = false;
        }
        else
        {
        }
    }
    gate = true;

    // gets the links
    for (int i = 0, temp1 = 0, temp2 = 0; i < numberOfLinks; i++)
    {
        cin >> temp1;
        cin >> temp2;
        // saves the value of the links in 2 nodes
        // becouse the links are 2-way
        node[temp1].getLink(temp2);
        node[temp2].getLink(temp1);

        // executes once and gets the index of the first node
        if (gate)
        {
            firstNode = temp1;
            gate = false;
        }
    }
}

// crawles a Node meaning it takes a node, checks all the links
// and if the link leades to a "not available" node
// marks the node as available and puts it in a waiting queue
// to be crawled
void crawl(cNodes node[], int selectedNode, stack<int> &waiting)
{

    // start of crawl
    for (int i = 0, selectedLink = 0; i < node[selectedNode].returnLinkCounter(); i++)
    {
        // gets a link value
        selectedLink = node[selectedNode].returnLink(i);

        // cheks if it is available
        if (node[selectedLink].returnAvailable())
        {
        }

        // if its not available, marks it as available
        // and puts it in a waiting queue
        else
        {
            node[selectedLink].availableT();
            waiting.push(selectedLink);
        }
    }
}

// checks if all nodes are connectet to the graph and
// if not, creates a link between the first node
// and the first not connected node
void checkNodes(cNodes node[], int numberOfNodes, int firstNode, bool &gate)
{
    // start of check
    for (int i = 0; i < numberOfNodes; i++)
    {
        // checks if a node is disconnected
        if (!node[i].returnAvailable())
        {
            // if a node is disconnected
            // creates a new link and breaks
            // the cycle
            node[firstNode].getLink(i);
            node[i].getLink(firstNode);
            gate = false;
            break;
        }
    }
}

int main()
{
    cNodes node[3000];
    int selectedNode = 0, numberOfNodes = 0, numberOfLinks = 0;
    int firstNode = 0, numberOfAddedLinks = 0;
    stack<int> waiting;
    bool gate = true;

    // gets user input
    getUserInput(node, numberOfNodes, numberOfLinks, firstNode);

    // selects the index of the first node
    selectedNode = firstNode;

    // marks the first node as available
    node[selectedNode].availableT();

    // this is the main code, the cycle breaks
    // when all the nodes are connected while
    // counting the newly created links
    while (true)
    {
        // pushes the first node into the waiting list so its not empty
        waiting.push(firstNode);

        // crawls thru nodes
        do
        {

            crawl(node, selectedNode, waiting);
            selectedNode = waiting.top();
            waiting.pop();

        } while (!waiting.empty());

        // cheks if all nods are connected
        gate = true;
        checkNodes(node, numberOfNodes, firstNode, gate);

        // if all nodes are connected the cycle breaks
        if (gate)
        {
            break;
        }

        // if there are disconnected nodes the cycle
        // continues and the number of added nodes
        // increases
        else
        {
            selectedNode = firstNode;
            numberOfAddedLinks++;
        }
    }

    // returns to the user the number of added links
    cout << numberOfAddedLinks;

    // end of code
    return 0;
}