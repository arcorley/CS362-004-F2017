/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.Random;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator();
	   //Test 1
	   System.out.println("*******TEST 1: http://www.amazon.com*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com") + "  Expected: true");
	   
	   //Test 2
	   System.out.println("*******TEST 2: https://google.com*******");
	   System.out.println("Returned: " + urlVal.isValid("https://google.com") + "  Expected: true");
	   
	   //Test 3
	   System.out.println("*******TEST 3: http://www.google.com/index.html*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.google.com/index.html") + " Expected: true");
	   
	   //Test 4
	   System.out.println("*******TEST 4: ftp://www.google.com/rfc/rfc1808.txt*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://www.google.com/rfc/rfc1808.txt") + "  Expected: true");
	   
	   //Test 5
	   System.out.println("*******TEST 5: https://www.google.ccom*******");
	   System.out.println("Returned: " + urlVal.isValid("https://www.google.ccom") + "  Expected: false");
	   
	   //Test 6
	   System.out.println("*******TEST 6: www.google.com*******");
	   System.out.println("Returned: " + urlVal.isValid("www.google.com") + "  Expected: false");
	   
	   //Test 7
	   System.out.println("*******TEST 7: https://www.google*******");
	   System.out.println("Returned: " + urlVal.isValid("https://www.google") + " Expected: false");
	   
	   //Test 8
	   System.out.println("*******TEST 8: http://  www.google.com*******");
	   System.out.println("Returned: " + urlVal.isValid("http://  www.google.com") + " Expected: false");
	   
	   //Test 9
	   System.out.println("*******TEST 9: http://100.100.100.100*******");
	   System.out.println("Return: " + urlVal.isValid("http://100.100.100.100") + " Expected: true");
	   
	   //Test 10
	   System.out.println("*******TEST 10: http://100.100.256.100*******");
	   System.out.println("Return: " + urlVal.isValid("http://100.100.256.100") + " Expected: false");
	   
	   //Test 11
	   System.out.println("*******TEST 11: http://www.google.com:30000/index.html*******");
	   System.out.println("Return: " + urlVal.isValid("http://www.google.com:30000/index.html") + " Expected: true");
	   
	   //Test 12
	   System.out.println("*******TEST 12: http://www.google.com:66000/index.html*******");
	   System.out.println("Return: " + urlVal.isValid("http://www.google.com:66000/index.html") + " Expected: false");
   }
   
   
   public void testYourFirstPartition()
   {
	   UrlValidator urlVal = new UrlValidator();
	   //Testing the first partition - the URL Scheme
	   System.out.println("*******TEST 13: htttp://www.amazon.com*******");
	   System.out.println("Returned: " + urlVal.isValid("htttp://www.amazon.com") + "  Expected: false");
	   
	   System.out.println("*******TEST 14: ftp:/www.amazon.com*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://www.amazon.com") + "  Expected: true");
	   
	   System.out.println("*******TEST 15: http://www.amazon.com*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://www.amazon.com") + "  Expected: true");
	   
	   System.out.println("*******TEST 16: http:/www.amazon.com*******");
	   System.out.println("Returned: " + urlVal.isValid("http:/www.amazon.com") + "  Expected: false");
	   
   }
   
   public void testYourSecondPartition(){
	   UrlValidator urlVal = new UrlValidator();
	   //Testing the second partition - the URL Authority
	   System.out.println("*******TEST 17: ftp://www.google.com*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://www.google.com") + "  Expected: true");
	   
	   System.out.println("*******TEST 18: ftp://255.255.255.255*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://255.255.255.255") + "  Expected: true");
	   
	   System.out.println("*******TEST 19: ftp://0.0.0.0*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://0.0.0.0") + "  Expected: true");
	   
	   System.out.println("*******TEST 20: ftp://256.256.256.256*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://256.256.256.256") + "  Expected: false");
	   
	   System.out.println("*******TEST 21: ftp://*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://") + "  Expected: false");
	   
	   System.out.println("*******TEST 22: ftp://1.2.3.4.5*******");
	   System.out.println("Returned: " + urlVal.isValid("ftp://1.2.3.4.5") + "  Expected: false");
	   
   }
   
   
   ResultPair[] testUrlScheme = 
   {	   new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("https://", true),
           new ResultPair("htttp://", false),
           new ResultPair("http:/", false)
   };

ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
              new ResultPair("google.com", true),
              new ResultPair("255.255.255.255", true),
              new ResultPair("0.0.0.0", true),
              new ResultPair("256.256.256.256", false),
              new ResultPair("", false),
              new ResultPair("1.2.3.4.5", false)
};
ResultPair[] testUrlPort = {new ResultPair(":80", true),
         new ResultPair(":65535", true),
         new ResultPair(":0", true),
         new ResultPair("", true),
         new ResultPair(":-1", false),
         new ResultPair(":aaa", false)
};
ResultPair[] testPath = {new ResultPair("/index.html", true),
      new ResultPair("/test//index.html", false),
      new ResultPair("/$23", true),
      new ResultPair("/test1/", true),
      new ResultPair("", true),
      new ResultPair("/test1/file", true)
};

ResultPair[] testUrlQuery = {new ResultPair("?test=true", true),
          new ResultPair("?test=true&anothertest=true", true),
          new ResultPair("", true),
          new ResultPair("&test=true", false)
};
   
   
   public void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator();
	   Random rand = new Random();
	   
	   for(int i = 0;i<10000;i++)
	   {
		   StringBuffer testBuffer = new StringBuffer();
		   boolean expected = true;
		   ResultPair result;
		   int randomNum;
		   
		   //grab pieces from the testUrl arrays
		   
		   //url scheme
		   randomNum = rand.nextInt(4) + 1; //get a random number between 0 and 4
		   result = testUrlScheme[randomNum]; 
		   testBuffer.append(result.item); //append the url scheme to the buffer
		   if (!result.valid) {
			   expected = false;
		   }
		   
		   //url authority
		   randomNum = rand.nextInt(6) + 1; //get a random number between 0 and 6
		   result = testUrlAuthority[randomNum];
		   testBuffer.append(result.item); //append the url authority to the buffer
		   if (!result.valid) {
			   expected = false;
		   }
		   
		   //url port
		   randomNum = rand.nextInt(5) + 1; //get a random number between 0 and 5
		   result = testUrlPort[randomNum];
		   testBuffer.append(result.item); //append the url port to the buffer
		   if (!result.valid) {
			   expected = false;
		   }
		   
		   //url path
		   randomNum = rand.nextInt(5) + 1; //get a random number between 0 and 5
		   result = testPath[randomNum];
		   testBuffer.append(result.item); //append the url port to the buffer
		   if (!result.valid) {
			   expected = false;
		   }
		   
		   //url query
		   randomNum = rand.nextInt(3) + 1; //get a random number between 0 and 5
		   result = testUrlQuery[randomNum];
		   testBuffer.append(result.item); //append the url port to the buffer
		   if (!result.valid) {
			   expected = false;
		   }
		   
		   String finalBuffer = testBuffer.toString();
		   
		   boolean outcome = urlVal.isValid(finalBuffer); 
		   if (outcome != expected)
		   {
			   System.out.println("Error found for url: " + finalBuffer + " Expected: " + expected + " Received: " + outcome);
		   }
		   assertEquals(finalBuffer, outcome, expected);
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   UrlValidator urlVal = new UrlValidator();
	   //Testing the third partition - the Url Port
	   System.out.println("*******TEST 23: http://www.amazon.com:80*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80") + "  Expected: true");
	   
	   System.out.println("*******TEST 24: http://www.amazon.com:65535*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:65535") + "  Expected: true");
	   
	   System.out.println("*******TEST 25: http://www.amazon.com:0*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:0") + "  Expected: true");
	   
	   System.out.println("*******TEST 26: http://www.amazon.com:-1*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:-1") + "  Expected: false");
	   
	   System.out.println("*******TEST 27: http://www.amazon.com*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com") + "  Expected: true");
	   
	   System.out.println("*******TEST 28: http://www.amazon.com:aaa*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:aaa") + "  Expected: false");
	  
	   //Testing the 4th partition - the Url Path
	   System.out.println("*******TEST 29: http://www.amazon.com:80*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80") + "  Expected: true");
	   
	   System.out.println("*******TEST 30: http://www.amazon.com:80/index.html*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/index.html") + "  Expected: true");
	   
	   System.out.println("*******TEST 31: http://www.amazon.com:80/test//index.html*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/test//index.html") + "  Expected: false");
	   
	   System.out.println("*******TEST 32: http://www.amazon.com:80/$23*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/$23") + "  Expected: true");
	   
	   System.out.println("*******TEST 33: http://www.amazon.com:80/test1/*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/test1/") + "  Expected: true");
	   
	   System.out.println("*******TEST 34: http://www.amazon.com:80/test1/file*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/test1/file") + "  Expected: true");
	   
	   //Testing the 5th partition - the Url Query
	   System.out.println("*******TEST 35: http://www.amazon.com:80/test1/?test=true*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/test1/?test=true") + "  Expected: true");
	   
	   System.out.println("*******TEST 36: http://www.amazon.com:80/test1/?test=true&anothertest=true*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/test1/?test=true&anothertest=true") + "  Expected: true");
	   
	   System.out.println("*******TEST 37: http://www.amazon.com:80/test1/&test=true*******");
	   System.out.println("Returned: " + urlVal.isValid("http://www.amazon.com:80/test1/&test=true") + "  Expected: false");
	  	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
