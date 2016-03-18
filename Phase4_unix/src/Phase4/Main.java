import java.io.File;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.NotDirectoryException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * File Name: Main.java
 * 
 * Description: This file is used as the main processing program for all of the back-end. 
 * 				It implements all the functions and objects created for the purpose of the 
 * 				back-end. This program will be used to maintain the back-end.
 * 
 * @author Dominick Mancini, Scott McLean, Janahan Nirmalan
 * @version 1.0.0
 *
 */
public class Main {
	
	public static void main(String[] args) throws FileNotFoundException, NotDirectoryException {
		
		//----------------DELETES PREVIOUS MERGED TRANSACTION FILE--------
		Path mergedPath = Paths.get("./merged_master_transactions.txt");
		try {
			Files.deleteIfExists(mergedPath);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//----------------------------------------------------------------
		File[] arrayOfTransactionFiles = Utilities.getIndividualTransactionFiles();
		
		File fMasterTransactionFile = Utilities.mergeFiles(arrayOfTransactionFiles, "merged_master_transactions.txt");
		File fOldMasterAccountsFile = new File(args[0]);
		File fNewMasterAccountsFile = new File("new_master_accounts.txt");
		File fNewCurrentAccounstFile = new File("current_accounts.txt");
		
		PrintWriter mPWriter = new PrintWriter(new FileOutputStream(fNewMasterAccountsFile, false));
		PrintWriter cPWriter = new PrintWriter(new FileOutputStream(fNewCurrentAccounstFile, false));
		
		//-----Redirects errors to a log file-----
		File file = new File("errors.log");
		FileOutputStream fos = new FileOutputStream(file);
		PrintStream ps = new PrintStream(fos);
		System.setErr(ps);
		//----------------------------------------
		
		Scanner scTransaction = new Scanner(fMasterTransactionFile);
		Scanner scAccounts = new Scanner(fOldMasterAccountsFile);
		
		ArrayList<Transaction> arrayOfTransactions = new ArrayList<Transaction>();
		ArrayList<Account> arrayOfMasterAccounts = new ArrayList<Account>();
		
		String transactionString;
		String acctString;
		
		boolean transactionSuccess;
		Transaction eofTransaction = new Transaction("00 XXXXXXXXXXXXXXXXXXXX 00000 99999.99 MM");
		
		System.out.println("Welcome to the Bank account system Backend.");
		
		//Read in accounts file
		System.out.println("Loading accounts...");
		while(scAccounts.hasNextLine()) {
			acctString = scAccounts.nextLine();
			if(acctString.length() != 44){
				System.err.println("ERROR: Invalid account:" + acctString);
			}
			else{
				arrayOfMasterAccounts.add(new Account(acctString));
			}
		}
		scAccounts.close();
		
		//Read in transactions file
		System.out.println("Reading transactions...");
		while(scTransaction.hasNextLine()) {
			transactionString = scTransaction.nextLine();
			if(transactionString.length() != 41){
				String culpritFile = Utilities.findFile(transactionString);
				System.err.println("ERROR: Invalid transaction, located in transaction file " + culpritFile + "."
						+ " Transaction: " + transactionString);
			}
			else {
				arrayOfTransactions.add(new Transaction(transactionString));
			}	
		}
		scTransaction.close();
		
		//-----------Process transactions-------------------
		System.out.println("Processing transactions...");
		for(Transaction t : arrayOfTransactions){
			transactionSuccess = Utilities.processTransaction(t, arrayOfMasterAccounts);
			if(!transactionSuccess){
				System.err.println("ERROR: Transaction \"" + t.transAsString() + "\" has failed.");
			}
		}
		Utilities.processTransaction(eofTransaction, arrayOfMasterAccounts);
		//---------------------------------------------------
		
		
		//-------------Write new Accounts Files--------------
		System.out.println("Writing new accounts file...");
		for (Account account : arrayOfMasterAccounts) {
			mPWriter.println(account.newAcctAsMasterString());
			System.out.println("Account: " + account.newAcctAsMasterString());
			cPWriter.println(account.newAcctAsCurrentString());
			System.out.println("Account: " + account.newAcctAsCurrentString());
		}
		mPWriter.close();
		cPWriter.close();
		//-----------------------------------------------------
		
		//---------------DELETE OLD ACCOUNTS FILE--------------
		Path acctMasterPath = fOldMasterAccountsFile.toPath();
		try {
			Files.deleteIfExists(acctMasterPath);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//-----------------------------------------------------
		
		//--------------REWRITE MASTER ACCOUNTS FILE-----------
		File newMasterName = new File(args[0]);
		if(fNewMasterAccountsFile.renameTo(newMasterName)){
			System.out.println("Master accounts file updated");
		}
		else{
			System.err.println("Could not write changes to master accounts file, changes must be manually applied."
					+ "\nChanges can be found in " + fNewMasterAccountsFile.getName());
		}
		//-----------------------------------------------------
	}
}
