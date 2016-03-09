package Phase4;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.NotDirectoryException;
import java.util.Scanner;

public class Utilities {
	
	public Utilities() {
		
	}
	
	@SuppressWarnings({ "resource", "null" })
	public String findFile(String fileText) throws NotDirectoryException, FileNotFoundException{
 		  String fileName = null;
		  File dir = new File("./");
		  File[] directoryListing = dir.listFiles();
		  if (directoryListing != null) {
		    for (File child : directoryListing) {
		      Scanner cScanner = new Scanner(child);
		      while(cScanner.hasNextLine()){
		    	  if(cScanner.nextLine().equals(fileText)){
		    		  fileName = child.getName();
		    	  }
		      }
		    }
		    if(fileName.isEmpty()){
		    	fileName = "File does not exist";
		    }
		  }
		  return fileName;
	}
}
