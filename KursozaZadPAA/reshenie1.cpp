/*
Softuer za obhojdane na grafi bez tegla
    --wseki node (wyzel) e obekt
    --wseki obekt ima 2 atributa links (rebra). countLinks (broi rebra)

Input:
    --wywejdat se 2 chisla na pyrwiqt red, 'n' i 'm', kato 'n' e broi nodes, a 'm' e broi links
    --na sledwashtite 'm' reda se wywejda wseki link mejdu 2 nodes
Output:
    --izwejda se edno chislo otgowarqshto na broqt links, koito trqbwa da bydat dobaweni za da se obhodqt wsichki nodes

Metod na rabota:
    --izbira se pyrwiqt wyweden node i se markira kato 'obhoden'
    --prowerqwat se negowite links i se izbira pyrwiqt neobhoden node
    --ako nowiqt node weche e markiran kato 'obhoden' se propuska
    --procesyt wse powtarq dokato ne se obhodqt wsichki wyzmojni nodes
    --sled obhojdaneto na grafa procesyt se wryshta na obratno
    --pri wryshtaneto se tyrsq links kym nodes koito ne sa poseteni
    --pri namirane na takyw se izbira nowiqt node
    --na kraq na obhojdaneto ako wse oshte ima nodes, koito ne sa obhodeni se dobawq link ot pyrwiqt node kym pyrwiqt neobhoden
    --kydeto cikylyt se powtarq


*/

#include <iostream>
#include <array>
#include <stack>

using namespace std;

// defining the object cNodes
class cNodes
{
private:
    int links[100];
    int countLinks = 0;
    int check = 0;

public:
    void getLinks(int temp)
    {
        links[countLinks] = temp;
        countLinks++;
    }
    int returnLink(int temp)
    {
        return links[temp];
    }
    int returnCountLinks()
    {
        return countLinks;
    }

    void checkT()
    {
        check = 1;
    }

    int returnCheck()
    {
        return check;
    }
};

void crawl (){
   
}



int main()
{

    cNodes node[100];
    stack<int> order;
    int countNodes = 0, countLinks = 0;
    int links[100][2];
    int selectedNode;
    int tempInt = 0;

    // get user input of the count of nodes and links
    cout << "\nBroi Wyzli i Rebra:";
    cin >> countNodes;
    cin >> countLinks;

    // get user input of links and sort them in nodes
    for (int i = 0; i < countLinks; i++)
    {

        cout << "Link " << i << ": ";
        cin >> links[i][0];
        cin >> links[i][1];

        node[links[i][0]].getLinks(links[i][1]);
        node[links[i][1]].getLinks(links[i][0]);
    }

    // select a starting node
    selectedNode = links[0][0];
    node[selectedNode].checkT();
    order.push(selectedNode);

    // start crawling thru the graph from the first node
    while (true)
    {

        // checking if the link of the selected node is used
        // if its not used the cycle is repeated with the next link
        if (node[node[selectedNode].returnLink(tempInt)].returnCheck())
        {
            tempInt++;

            // if the all the links are used in the selcted node
            // the cycle stops
            if (node[selectedNode].returnCountLinks() + 1 == tempInt)
            {
                tempInt = 0;
                break;
            }
        }

        // if the link is not used we select the new node, mark it as
        // crawled, we put it in a stack and we reset the counter
        // for crawled links
        else
        {
            selectedNode = node[selectedNode].returnLink(tempInt);
            node[selectedNode].checkT();
            order.push(selectedNode);
            tempInt = 0;
        }
    }

    //start crawling the graph from the last cheked node
    while(!order.empty()){

        //selecting the last checked node
        selectedNode = order.top();

        //checking the selected node links
        if (node[node[selectedNode].returnLink(tempInt)].returnCheck())
        {
            tempInt++;

            //checking if the link is the last in the node
            if (node[selectedNode].returnCountLinks() + 1 == tempInt)
            {
                tempInt = 0;
                order.pop();
            }

        }
        else{
            //trqbwa da se naprawqt funcii koito da obhajdat nazad i napred

        }

    }


    return 0;
}