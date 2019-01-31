#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/error.h"
#include "rapidjson/error/en.h"
#include <inttypes.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <boost/shared_ptr.hpp>

int main() {
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10 }";
    rapidjson::Document d;
    if(d.Parse(json).HasParseError()) {
        fprintf(stderr, "\nError(offset %u): %s\n",
            (unsigned)d.GetErrorOffset(),
            GetParseError_En(d.GetParseError()));
    }
    // 2. Modify it by DOM.
    rapidjson::Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    uint64_t xx = 20982098;
    char format[100];
    sprintf(format, "my name is 0x%" PRIx64 "\n", xx);
    printf(format, xx);

    int p = s.GetInt();
    std::cout << "value of p:" << p << " " << d["stars"].GetInt() << std::endl;

    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;

    rapidjson::Document person(rapidjson::kObjectType);
    rapidjson::Document::AllocatorType& allocator = person.GetAllocator();
    person.AddMember("name", "satish", allocator);
    person.AddMember("age", 30, allocator);
    std::cout << "age " << person["age"].GetInt() << std::endl;
    std::cout << "name " << person["name"].GetString() << std::endl;

    rapidjson::Document city(rapidjson::kObjectType);
    city.AddMember("name", "Fremont", allocator);
    city.AddMember("population", 26387, allocator);

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    std::time_t startTime = std::chrono::system_clock::to_time_t(start);

    uint64_t x = static_cast<uint64_t>(startTime);
    city.AddMember("time", x, allocator);

    rapidjson::Value areas(rapidjson::kArrayType);
    areas.PushBack("irving", allocator);
    areas.PushBack("arden", allocator);
    city.AddMember("areas", areas, allocator);

    /* old way - use SetObject() */
    rapidjson::Document lDoc;
    lDoc.SetObject();
    rapidjson::Value tests(rapidjson::kArrayType);
    tests.PushBack("hello", lDoc.GetAllocator());
    tests.PushBack("world", lDoc.GetAllocator());
    lDoc.AddMember("tests", tests, lDoc.GetAllocator());
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> mw(strbuf);
    lDoc.Accept(mw);
    std::cout << "Just testing " << strbuf.GetString() << std::endl;

    /* Still older - use writer to create json */
    strbuf.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> riter(strbuf);
    riter.StartObject();
    riter.Key("hello");
    riter.String("world");

    riter.String("cities");
    riter.StartArray();
    riter.StartObject();
    riter.Key("name");
    riter.String("koderma");
    riter.Key("popu");
    riter.Uint(2000);
    riter.EndObject();

    riter.StartObject();
    riter.Key("name");
    riter.String("dhanwar");
    riter.Key("popu");
    riter.Uint(3000);
    riter.EndObject();

    riter.EndArray();
    riter.EndObject();	//end main json
    std::string jsonStr = strbuf.GetString();
    std::cout << "Just old " << jsonStr << std::endl;

    //parse and update json
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());
    std::cout << "parse: " << doc["hello"].GetString() << std::endl;
    doc.AddMember("state", "jharkhand", doc.GetAllocator());

    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer2(sb);
    doc.Accept(writer2);    // Accept() traverses the DOM and generates Handler events.
    std::cout << "full json " << sb.GetString() << std::endl;

    std::cout << "popu " << city["population"].GetInt() << std::endl;
    std::cout << "name " << city["name"].GetString() << std::endl;
    std::cout << "time " << city["time"].GetUint64() << std::endl;
    std::cout << "time " << startTime << std::endl;

    std::string tok = "eyJ0eXAiOiJqd3QiLCJhbGciOiJSUzI1NiJ9.eyJkb21haW5zIjpbeyJuYW1lIjoiYWxsIiwicm9sZXNSIjowLCJyb2xlc1ciOjF9XSwiaXNzIjoidG9wb2xvZ3kvcG9kLTEvbm9kZS0xIiwic3ViIjoiYWRtaW4iLCJhdWQiOiJBUElDLUFwcHMiLCJpYXQiOjE1MjcyMDI5MzcsImV4cCI6MTUyNzIwNjUzNywic2Vzc2lvbklkIjoiKPWO74Y2Sfal3dQpXHUwMDEzo1x1MDAxMNh5RFx1MDAwN1t5RFx1MDAwN1s_XHUwMDE1Iiwic2l0ZUZpbmdlcnByaW50IjoicHpjeFJVckRIRGpoVzFsVyJ9.GzYMbduUquP5KIIwB9wUndRfehbqqRZFl2INFrGeMkbruuF_RKJ4FnuM0Cv2oqgCTT74BO0LAlfi3MxnlEUm0anmnKF62Mw6WQiu6cBirZwcN8JCQP3MqFsqJvy3cw2SOlHZmcVkD4yVWwiyH9-ce5cdTL2GYpBxUGCGYN0WrI9qDwGV0TzHM8VwMK7gWWSwcXQzp0aW7DJ0N3RiPajy66RG7JzpQkj8w7qN1PZeAJFC2_4lw3LadU0-fRn24kHduRzQAO_SMqRnJmnEbT50OyeTGTtoHr9f83wkX3KNKFBIRhLhFhavs1VonlY-HiGsV8Oc5upiKayBSnSrkXlTnA";
    size_t pos = tok.find('.', 0);
    std::string subtok = tok.substr(0, pos);
    std::cout << "sub token is " << subtok << std::endl;

    return 0;
}
