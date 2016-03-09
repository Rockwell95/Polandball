package Phase4;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.NotDirectoryException;
import java.util.ArrayList;
import java.util.Scanner;

public class Utilities {
	
	public Utilities() {}
	
	@SuppressWarnings({ "resource" })
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
		return String.format("%05d", num);
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
	
	public static int createNewAccountNumber(ArrayList<Account> existingAccounts){
		int highestNum = getHighestAcctNum(existingAccounts);
		return highestNum + 1;
	}
	
	public static Account getAccountByNumber(String acctNum, ArrayList<Account> arrayOfAccounts){
		Account acct = null;
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
		boolean transactionSuccess = false;
		Account acct = Utilities.getAccountByNumber(t.getAccountNumber(), accounts);
		if(acct.getStatus() == 'D'){
			transactionSuccess = false;
			System.out.println("ERROR Account with number " + t.getAccountNumber() +" is Disabled");
		}
		
		switch (sTransNum) {
		case "00":
			System.out.println("End of session.");		
			break;
		case "01":
			System.out.println("Transaction: Withdrawal");
			transactionSuccess = TransactionProcessor.withdrawal(t, acct);
			break;
		case "02":
			System.out.println("Transaction: Transfer, you should not be seeing this");
			transactionSuccess = TransactionProcessor.transfer(t, acct);
			break;
		case "03":
			System.out.println("Transaction: Pay Bill");
			transactionSuccess = TransactionProcessor.paybill(t, acct);
			break;
		case "04":
			System.out.println("Transaction: Deposit");
			transactionSuccess = TransactionProcessor.deposit(t, acct);
			break;
		case "05":
			System.out.println("Transaction: Create");
			transactionSuccess = TransactionProcessor.create(t, acct);
			break;
		case "06":
			System.out.println("Transaction: Delete");
			transactionSuccess = TransactionProcessor.delete(t, acct);
			break;
		case "07":
			System.out.println("Transaction: Disable");
			transactionSuccess = TransactionProcessor.disable(t, acct);
			break;
		case "08":
			System.out.println("Transaction: Change Plan");
			transactionSuccess = TransactionProcessor.changeplan(t, acct);
			break;
		case "09":
			System.out.println("Transaction: Enable");
			transactionSuccess = TransactionProcessor.enable(t, acct);
			break;

		default:
			System.err.println("ERROR: Transaction ID " + sTransNum + " is unknown.\nTransaction: " + t.transAsString());
			transactionSuccess = false;
			break;
		}
		return transactionSuccess;
	}
}
