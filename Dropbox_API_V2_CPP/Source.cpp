#include <cpprest/http_client.h>
#include <functional>

using namespace web::http::client;
using namespace web::http;
using namespace web::json;

std::function<void(std::wstring)> Log = [](std::wstring message) { std::wcout << message << std::endl; };

int main(int argc, char* argv[])
{
	std::wstring accountId = L"your accountId";
	std::wstring accessToken = L"your accessToken";

	http_client client(U("https://api.dropboxapi.com"));


	http_request request(methods::POST);
	request.headers().add(L"Authorization", L"Bearer " + accessToken);
	request.headers().add(L"Content-Type", L"application/json");
	request.set_request_uri(L"2/users/get_account");

	value postParameters = value::object();
	postParameters[L"account_id"] = value::string(accountId);

	request.set_body(postParameters);

	client.request(request)
	      .then([=](http_response response)
		      {
			      value const& json = response.extract_json().get();
			      auto nameObj = json.at(L"name");

			      Log(L"Name: " + nameObj.at(L"given_name").to_string());
			      Log(L"Surname: " + nameObj.at(L"surname").to_string());
		      })
	      .wait();
}
