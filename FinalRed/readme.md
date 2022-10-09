## Задача по программированию: Поисковая система  

### В этой задаче вам надо поработать с классом SearchServer, который позволяет выполнять поиск в базе документов:

    class SearchServer {
    public:
      SearchServer() = default;
      explicit SearchServer(istream& document_input);

      void UpdateDocumentBase(istream& document_input);
      void AddQueriesStream(istream& query_input, ostream& search_results_output);
    };


