package Phase4;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.file.NotDirectoryException;
import java.util.ArrayList;
import java.util.Scanner;

public class Utilities {

	//Creates an array of Transaction files
	public static File[] getIndividualTransactionFiles()throws NotDirectoryException{ 
	  File dir = new File("./transaction files/");
	  File[] transactionFiles = dir.listFiles();
	  if (transactionFiles == null) {
		  System.err.println("ERROR: Could not find individual transaction Files, file list is empty");
	  }
	  return transactionFiles;
		  
	}
	
	//Borrowed from <http://www.programcreek.com/2012/09/merge-files-in-java/>
	public static File mergeFiles(File[] files, String name) {
		
		File mergedFile = new File(name);
		FileWriter fstream = null;
		BufferedWriter out = null;
		try {
			fstream = new FileWriter(mergedFile, true);
			out = new BufferedWriter(fstream);
		} 
		catch (IOException e1) {
			e1.printStackTrace();
		}
 
		for (File f : files) {
			System.out.println("merging: " + f.getName());
			FileInputStream fis;
			try {
				fis = new FileInputStream(f);
				BufferedReader in = new BufferedReader(new InputStreamReader(fis));
 
				String aLine;
				while ((aLine = in.readLine()) != null) {
					out.write(aLine);
					out.newLine();
				}
 
				in.close();
			} 
			catch (IOException e) {
				e.printStackTrace();
			}
		}
 
		try {
			out.close();
		} 
		catch (IOException e) {
			e.printStackTrace();
		}
		return mergedFile;
 
	}
	
	@SuppressWarnings("resource")
	public static String findFile(String fileText) throws NotDirectoryException, FileNotFoundException{
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
	
	public static String padSpaceRight(String s, int n) {
	     return String.format("%1$-" + n + "s", s);  
	}

	public static String padSpaceLeft(String s, int n) {
	    return String.format("%1$" + n + "s", s);  
	}
	
	public static String padZeroesLeft (String num, int size){
		return String.format("%0" + size + "d", Integer.parseInt(num));
	}
	
	public static int getHighestAcctNum (ArrayList<Account> arrayOfAcconts){
		int highest = 0;
		for (int i = 0; i < arrayOfAcconts.size(); i++) {
			if(Integer.parseInt(arrayOfAcconts.get(i).getNumber()) > highest){
				highest = Integer.parseInt(arrayOfAcconts.get(i).getNumber());
			}
		}
		return highest;
	}
	
	public static String createNewAccountNumber(ArrayList<Account> existingAccounts){
		int highestNum = getHighestAcctNum(existingAccounts);
		return padZeroesLeft(Integer.toString(highestNum + 1), 5);
	}
	
	public static Account getAccountByNumber(String acctNum, ArrayList<Account> arrayOfAccounts){
		Account acct = new Account("00000", "XXXXXXXXXXXXXXXXXXXX");
		for (Account account : arrayOfAccounts) {
			if(account.getNumber().equals(acctNum)){
				acct = account;
				break;
			}
		}
		return acct;
	}
	
	public static boolean processTransaction(Transaction t, ArrayList<Account> accounts){
		String sTransNum = t.getTransactionNumber();
		System.out.println("Transaction number: " + sTransNum);
		boolean transactionSuccess = false;
		Account acct = Utilities.getAccountByNumber(t.getAccountNumber(), accounts);
		// Create is a special case, as no account will exist, 
		// so the program should still allow execution even if
		// the account is not "Active", so to speak. Furthermore
		// Enable will only work on a disabled account.
		if(acct.getStatus() != 'A' && !sTransNum.equals("05") && !sTransNum.equals("09")){
			transactionSuccess = false;
			System.err.println("ERROR Account with number " + t.getAccountNumber() +". Account is Disabled");
		}
		else if(sTransNum.equals("00")){
			System.out.println("End of session.");	
		}
		else if(sTransNum.equals("01")){
			System.out.println("Transaction: Withdrawal");
			transactionSuccess = TransactionProcessor.withdrawal(t, acct);
		}
		else if(sTransNum.equals("02")){
			System.out.println("Transaction: Transfer, you should not be seeing this");
			transactionSuccess = TransactionProcessor.transfer(t, acct);
		}
		else if(sTransNum.equals("03")){
			System.out.println("Transaction: Pay Bill");
			transactionSuccess = TransactionProcessor.paybill(t, acct);
		}
		else if(sTransNum.equals("04")){
			System.out.println("Transaction: Deposit");
			transactionSuccess = TransactionProcessor.deposit(t, acct);
		}
		/*!-----BEGIN ADMIN TRANSACTIONS-----!*/
		else if(sTransNum.equals("05")){//Special case
			System.out.println("Transaction: Create");
			transactionSuccess = TransactionProcessor.create(t, accounts);
		}
		else if(sTransNum.equals("06")){
			System.out.println("Transaction: Delete");
			transactionSuccess = TransactionProcessor.delete(t, acct, accounts);
		}
		else if(sTransNum.equals("07")){
			System.out.println("Transaction: Disable");
			transactionSuccess = TransactionProcessor.disable(t, acct);
		}
		else if(sTransNum.equals("08")){
			System.out.println("Transaction: Change Plan");
			transactionSuccess = TransactionProcessor.changeplan(t, acct);
		}
		else if(sTransNum.equals("09")){
			System.out.println("Transaction: Enable");
			transactionSuccess = TransactionProcessor.enable(t, acct);
		}
		/*!-----END ADMIN TRANSACTIONS-----!*/
		else{
			System.err.println("ERROR: Transaction ID " + sTransNum + " is unknown.\nTransaction: " + t.transAsString());
			transactionSuccess = false;
		}
		return transactionSuccess;
	}
}
