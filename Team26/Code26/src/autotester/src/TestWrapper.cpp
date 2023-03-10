#include "TestWrapper.h"
#include "qps/QueryManager.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;


// a default constructor
TestWrapper::TestWrapper() {
    // create any objects here as instance variables of this class
    // as well as any initialization required for your spa program
    this->pkbInterface = new PKBInterface();
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
    try {
        // Read the file first
        std::ifstream sourceFile;
        sourceFile.open(filename);
        if (!sourceFile) {
            std::cout << "No such file!" << std::endl;
            exit(1);
        }
        std::string sourceProgram;
        while (!sourceFile.eof()) {
            std::string newLine;
            getline(sourceFile, newLine);
            sourceProgram += newLine;
        }

        // Create SourceProcessor and parse to PKB
        SourceProcessor sourceProcessor = SourceProcessor(this->pkbInterface);
        sourceProcessor.processSIMPLE(sourceProgram);
    } catch (SyntaxErrorException e) {
        std::cout << e.what() << std::endl;
        exit(1);
    } catch (SemanticErrorException e) {
        std::cout << e.what() << std::endl;
        exit(1);
    } catch (EndOfFileException e) {
        // This case should never happen but catching it here for completeness
        std::cout << e.what() << std::endl;
        exit(1);
    }
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...
    QPS::QueryManager queryManager = QPS::QueryManager();
//    std::cout << "==== evaluate======" << std::endl;
//    std::cout << query << std::endl;
    queryManager.handleQuery(pkbInterface, query, results);

    // store the answers to the query in the results list (it is initially empty)
    // each result must be a string.
}

TestWrapper::~TestWrapper() {
    delete this->pkbInterface;
}
