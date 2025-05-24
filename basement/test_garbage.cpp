
 #include <iostream>
 using namespace std;
 using namespace dsj;





 static void testPlayNiceSTLForEach() {
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     REQUIRE( container.size() == 10);
     int index = 0;
     for_each( begin(container),end(container),[&](std::pair<int,float> p) {
         REQUIRE(p.first == index);
         index ++;
     });
 }

 static void testGetValues()
 {
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     REQUIRE(container.size() == 10);
     container.getValues().forEach ( [&](int aValue){
         cout << aValue << endl;
         //REQUIRE(aValue == 1.1234 * index );
     });
 }

 static void testForEach()
 {
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     REQUIRE(container.size() == 10);
     auto selector = [](std::pair<int,float> p ){
         cout << p.first << ":" << p.second << endl;
     };
     container.forEach(selector);
 }

 static void testGetKeys()
 {
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     REQUIRE(container.size() == 10);
     int index = 0;
     container.getKeys().forEach ( [&](int aKey){
         REQUIRE(aKey == index);
         cout << aKey << ":" << container[aKey] << ":" << (1.1234 * (float) index) << endl;
         //REQUIRE( container[aKey].second == (1.1234 * (float) index) );
         index ++;
     });
 }

 static void testMap()
 {
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = M_PI * (float) i;
     }
     REQUIRE(container.size() == 10);

     auto mapper = [&] (std::pair<int,float> &p ) -> std::pair<long,double> {
         std::pair<long,double> newP;
         newP.first = (double) 10* p.first;
         newP.second = (double) M_PI * p.second;
         return newP;
     };

     auto filtered =container.map<long,double>(mapper);

     int i = 0;
     long l = 0;
     filtered.forEach ( [&]( std::pair<long,double> p){
         std::cout << p.first << ":" << p.second << std::endl;
         REQUIRE( p.first == (double) l * 10.0 );
 //        auto _d =  M_PI * (float) i;
 //        REQUIRE( p.second == _d );
         l++; i++;
     });
 }

 static void testForEachReverse()
 {
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     REQUIRE(container.size() == 10);
     auto selector = [](std::pair<int,float> p ){
         cout << p.first << ":" << p.second << endl;
     };
     container.forEachReverse(selector);
 }
 TEST_CASE("testForEachReverse","[0]"){
     testForEachReverse();
 }



 TEST_CASE("testGetKeys","[0]"){
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     REQUIRE(container.size() == 10);
     int index = 0;
     container.getKeys().forEach ( [&](int aKey){
         REQUIRE(aKey == index);
         cout << aKey << ":" << container[aKey] << ":" << (1.1234 * (float) index) << endl;
         //REQUIRE( container[aKey].second == (1.1234 * (float) index) );
         index ++;
     });
 }


 TEST_CASE("testGetValues","[0]"){
     testGetValues();
 }



 TEST_CASE("testForEach","[0]"){
     testForEach();
 }


 TEST_CASE("container.filter") {
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     REQUIRE(container.size() == 10);
     auto selector = [](std::pair<int,float> p ){
         return p.first % 2 == 0;
     };
     auto filtered =container.filter(selector);

     filtered.forEach ([](auto p){
         REQUIRE( p.first % 2 == 0);
     });
 }




 TEST_CASE("testMap","[0]"){
     testMap();
 }


 void testPlayNiceSTLBeginEndIterator (){
     REQUIRE( container.size() == 10);
     int index = 0;
     for ( auto it = begin(container); it!=end(container);it++){
         REQUIRE( it->first == index  );
         //REQUIRE( it->second == (float)index *  1.1234 );
         index++;
     }
 }


 TEST_CASE("std::fro_each"){
     easy_map<int,float> container;
     for ( int i =0 ; i < 10; i++){
         container[i] = 1.1234 * (float) i;
     }
     //REQUIRE( container.size() == 10);
     int index = 0;
     for_each( begin(container),end(container),[&](std::pair<int,float> p) {
         REQUIRE(p.first == index);
         index ++;
     });
 }
