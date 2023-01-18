#include <iostream>
#include <string>
#include "leveldb/db.h"
#include "rapidjson/document.h"
#include "stats.h"
#include <fstream>
#include "cxxopts.hpp"
#include <stdio.h>
#include <climits>
#include "param.h"


//std::string generateJSON(std::string k, std::string v) {
//    return "{\"City\": \"" + k + "\",\"State\": \"" + v + "\"}";
//}

std::string generateJSON(std::string pkey, std::string skey) {
//    return "{\"A\": \"" + pkey + "\",\"B\": \"" + skey + "\",\"C\": \"" + std::string(1, '0') + "\"}";
    return "{\"A\": \"" + pkey + "\",\"B\": \"" + skey + "\"}";
}

void print_vals(std::vector<leveldb::KeyValuePair>& vals) {
    FILE *fp = fopen("results_output.txt", "a");
  for(std::vector<leveldb::KeyValuePair>::iterator it = vals.begin(); it != vals.end(); ++it)
//    std::cout << "key: " << it->key.data() << " value: " << it->value.data() << std::endl;
        fprintf(fp, "key: %s value: %s\n", it->key.data(), it->value.data());
    fclose(fp);
}


int main(int argc, char** argv) {

    std::string PATH;

    cxxopts::Options commandline_options("leveldb read test", "Testing leveldb read performance.");
    commandline_options.add_options()
      ("m,mod", "whether to learn secondary keys", cxxopts::value<int>(mod::MOD)->default_value(0))
      ("d,dataset", "the dataset to be tested", cxxopts::value<std::string>(PATH)->default_value("../dataset/1.0_1000000.csv"));
    auto result = commandline_options.parse(argc, argv);
    if (result.count("help")) {
        printf("%s", commandline_options.help().c_str());
        exit(0);
    }

    //
    //************************************************************************************
    leveldb::DB* db;
    leveldb::Options options;
    mod::Stats* ins = mod::Stats::GetInstance();
    FILE *fp = fopen(PATH.data(),"r");
    std::string line;

    options.create_if_missing = true;
    options.using_s_index = true;
    options.primary_key = "A";
    options.secondary_key = "B";

    std::cout << "Trying to create database\n";
    if (!leveldb::DB::Open(options, "/tmp/LSIM", &db).ok()) return 1;
    std::cout << "Created databases\n";

    // insert some key-value pairs
    leveldb::WriteOptions woptions;
    std::string val;
    leveldb::Status s;

    int indicator = 1;
    std::cout << "Trying to write values\n";
    while (!feof(fp)) {
        int num1, num2;
        fscanf(fp, "%d,%d", &num1, &num2);
        val = generateJSON(std::to_string(num1), std::to_string(num2));
        s = db->Put(woptions, val);
        assert(s.ok());
        printf("写入进度: %d\r", indicator++);
    }

    //*/
    std::cout << "\nFinished writing values\n";
//    std::cout << "\nDeleting values\n";
//
//    val = "Springfield";
//    s = db->Delete(woptions, val);
//    assert(s.ok());

//    std::cout << "\nFinished deleting values\n";
    int kNumberLevels = db -> GetKNumberLevels();
    std::cout << "LevelDB主索引的最后一层数字编号: " << kNumberLevels << std::endl;

    std::cout << "\nReading back values\n";

      //* // read them back
    leveldb::ReadOptions roptions;
    std::string skey;
    std::vector<leveldb::KeyValuePair> ret_vals;
    leveldb::Status s2;

    remove("results_output.txt");
    indicator = 0;
    for (int i = 1; i <= 100; i += 1) {
        skey = std::to_string(i);
        roptions.num_records = INT_MAX;
        s2 = db->Get(roptions, skey, &ret_vals);
        assert(s2.ok());
        print_vals(ret_vals);
        ret_vals.clear();
        printf("读进度: %d\r", indicator++);
    }
    std::cout << "\nFinished reading values\n";

    for (int i = 0; i <= 7; i += 1) {
        uint64_t time_test = ins -> ReportTime(i);
//        printf("Timer %d: %lu\n", i, time_test / 100);
    }

    //************************************************************************************
    //

    #if 0
    leveldb::DB* db;
    leveldb::Options options;

    options.create_if_missing = true;

    options.using_s_index = true;
    options.primary_key = "City";
    options.secondary_key = "State";

    if (!leveldb::DB::Open(options, "./testdb", &db).ok()) return 1;


        // insert some key-value pairs
    leveldb::WriteOptions woptions;
    string val;

        val = generateJSON("Riverside", "California");
        leveldb::Status s = db->Put(woptions, val);
        assert(s.ok());

        val = generateJSON("Los Angeles", "California");
        s = db->Put(woptions, val);
        assert(s.ok());

        val = generateJSON("San Diego", "California");
        s = db->Put(woptions, val);
        assert(s.ok());

        val = generateJSON("Miami", "Florida");
        s = db->Put(woptions, val);
        assert(s.ok());

        val = generateJSON("Springfield", "Illinois");
        s = db->Put(woptions, val);
        assert(s.ok());

        val = generateJSON("Springfield", "Massachusetts");
        s = db->Put(woptions, val);
        assert(s.ok());

        val = generateJSON("Los Angeles", "California");
        s = db->Put(woptions, val);
        assert(s.ok());


    /*    // read them back
    leveldb::ReadOptions roptions;
    string skey;
    vector<leveldb::KeyValuePair> ret_vals;

        skey = "California";
        leveldb::Status s2 = db->Get(roptions, skey, ret_vals);
        assert(s2.ok());
        print_vals(ret_vals);

        ret_vals.clear();
        skey = "Florida";
        db->Get(roptions, skey, ret_vals);
        print_vals(ret_vals);

        ret_vals.clear();
        skey = "Illinois";
        db->Get(roptions, skey, ret_vals);
        print_vals(ret_vals);

        ret_vals.clear();
        skey = "Massachusetts";
        db->Get(roptions, skey, ret_vals);
        print_vals(ret_vals);
    //*/

    //*
    cout << "\nPrimary db contents:\n";
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

    for (it->SeekToFirst(); it->Valid(); it->Next())
      cout << it->key().data() << " : " << it->value().data() << endl;

    if (false == it->status().ok())
      cerr << "An error was found during the scan" << endl << it->status().ToString() << endl;

    delete it;

    cout << "\nSecondary db contents:\n";
    leveldb::Iterator* sit = db->sdb->NewIterator(leveldb::ReadOptions());

    for (sit->SeekToFirst(); sit->Valid(); sit->Next())
      cout << sit->key().data() << " : " << sit->value().data() << endl;

    if (false == sit->status().ok())
      cerr << "An error was found during the scan" << endl << it->status().ToString() << endl;

    delete sit; //*/

    delete db;

    #endif

}
