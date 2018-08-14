

import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   /*
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
	   
   }
   */
   public void testFirstPartition()
   {
	   System.out.print("ALLOW_2_SLASHES:\n");
	   
	   String scheme = "https://";
	   String port = ":555";
	   String path = "/test/path";
	   String query = "?query=true&anotherVar=yes";
	   String baseURL = "www.google.com";
	   for(int i = 0; i < 210; i++) {
		   boolean expected = true;
		   String theURL = baseURL;
		   if(i % 2 == 0) {
			   theURL = scheme + theURL;
		   }
			   
		   if(i % 3 == 0) {
			   theURL = theURL + port;
		   }
			   
		   if(i % 5 == 0) {
			   theURL = theURL + path;
		   }
			   
		   if(i % 7 == 0) {
			   theURL = theURL + query;
		   }
		   
		   testFirstPartition(theURL, expected);
	   }
   }
   
   public void testSecondPartition()
   {
	   System.out.print("NO_FRAGMENTS:\n");
	   
	   String scheme = "https://";
	   String port = ":555";
	   String path = "/test/path";
	   String query = "?query=true&anotherVar=yes";
	   String baseURL = "www.google.com";
	   for(int i = 0; i < 210; i++) {
		   boolean expected = true;
		   String theURL = baseURL;
		   if(i % 2 == 0) {
			   theURL = scheme + theURL;
		   }
			   
		   if(i % 3 == 0) {
			   theURL = theURL + port;
		   }
			   
		   if(i % 5 == 0) {
			   theURL = theURL + path;
		   }
			   
		   if(i % 7 == 0) {
			   theURL = theURL + query;
		   }
		   
		   testSecondPartition(theURL, expected);
	   }
   }
   
   public void testThirdPartition()
   {
	   System.out.print("ALLOW_LOCAL_URLS:\n");
	   
	   String scheme = "https://";
	   String port = ":555";
	   String path = "/test/path";
	   String query = "?query=true&anotherVar=yes";
	   String baseURL = "www.google.com";
	   for(int i = 0; i < 210; i++) {
		   boolean expected = true;
		   String theURL = baseURL;
		   if(i % 2 == 0) {
			   theURL = scheme + theURL;
		   }
			   
		   if(i % 3 == 0) {
			   theURL = theURL + port;
		   }
			   
		   if(i % 5 == 0) {
			   theURL = theURL + path;
		   }
			   
		   if(i % 7 == 0) {
			   theURL = theURL + query;
		   }
		   
		   testThirdPartition(theURL, expected);
	   }
   }
   
   public void testFourthPartition()
   {
	   System.out.print("ALLOW_ALL_SCHEMES:\n");
	   
	   String scheme = "https://";
	   String port = ":555";
	   String path = "/test/path";
	   String query = "?query=true&anotherVar=yes";
	   String baseURL = "www.google.com";
	   for(int i = 0; i < 210; i++) {
		   boolean expected = true;
		   String theURL = baseURL;
		   if(i % 2 == 0) {
			   theURL = scheme + theURL;
		   }
			   
		   if(i % 3 == 0) {
			   theURL = theURL + port;
		   }
			   
		   if(i % 5 == 0) {
			   theURL = theURL + path;
		   }
			   
		   if(i % 7 == 0) {
			   theURL = theURL + query;
		   }
		   
		   testFourthPartition(theURL, expected);
	   }
   }
   
   public void testFirstPartition(String theURL, boolean expected)
   {
	   try{
		   
           UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
           boolean result = urlVal.isValid(theURL);

           if(result == expected) {
               System.out.print(theURL + ": Pass\n");
           } else {
               System.out.print(theURL + ": FAIL\n");
           }
       } catch (Error theEx) {
           System.out.print(theURL + ": Exception\n");
       }
   }
   
   public void testSecondPartition(String theURL, boolean expected){
	   try{
		   
           UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
           boolean result = urlVal.isValid(theURL);

           if(result == expected) {
               System.out.print(theURL + ": Pass\n");
           } else {
               System.out.print(theURL + ": FAIL\n");
           }
       } catch (Error theEx) {
           System.out.print(theURL + ": Exception\n");
       }
   }
   
   public void testThirdPartition(String theURL, boolean expected){
	   try{
		   
           UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
           boolean result = urlVal.isValid(theURL);

           if(result == expected) {
               System.out.print(theURL + ": Pass\n");
           } else {
               System.out.print(theURL + ": FAIL\n");
           }
       } catch (Error theEx) {
           System.out.print(theURL + ": Exception\n");
       }
 }
   
   public void testFourthPartition(String theURL, boolean expected){
	   try{
           UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
           boolean result = urlVal.isValid(theURL);

           if(result == expected) {
               System.out.print(theURL + ": Pass\n");
           } else {
               System.out.print(theURL + ": FAIL\n");
           }
       } catch (Error theEx) {
           System.out.print(theURL + ": Exception\n");
       }
 }

}
