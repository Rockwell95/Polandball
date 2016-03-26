package Phase4;

import static org.junit.Assert.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.nio.file.NotDirectoryException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Scanner;

import org.junit.Test;

public class TransactionTesting {
	
	//----GLOBAL VARIABLES FOR MASTER ACCOUNTS FILE-----------------------
	private String acctLine;
	private ArrayList<Account> arrayOfAccounts = new ArrayList<Account>();
	//--------------------------------------------------------------------
	
	@Test
	public void test() throws FileNotFoundException, NotDirectoryException{
		
		//-----------DELETES PREVIOUS MERGED TEST TRANSACTION FILE--------
		Path mergedPath = Paths.get("./transaction_tests/merged_test_files/merged_master_transactions.txt");
		Utilities.tryDelete(mergedPath);
		//----------------------------------------------------------------
		
		//--------------INITIALIZE VARIABLES------------------------------
		ArrayList<Boolean> testOutputs = new ArrayList<Boolean>();
		
		String transactionLine;
		
		//List of Accounts and Transactions
		ArrayList<Transaction> arrayOfTransactions = new ArrayList<Transaction>();
		
		ArrayList<File> resultFiles = new ArrayList<File>();
		ArrayList<File> expectedFiles = new ArrayList<File>();
		
		File[] trans = Utilities.getIndividualTransactionFiles("./transaction_tests/test_files/");
		File masterTransactionFile = Utilities.mergeFiles(trans, "./transaction_tests/merged_test_files/merged_master_transactions.txt");
		
		Scanner transScanner = new Scanner(masterTransactionFile);
		//----------------------------------------------------------------
		
		//Sets arrayOfAccounts to what is in the master accounts file before first test
		resetAccounts();
		
		
		
		//----------READS EACH TRANSACTION--------------------------------
		while(transScanner.hasNextLine()){
			transactionLine = transScanner.nextLine();
			if(transactionLine.length() == 41){
				arrayOfTransactions.add(new Transaction(transactionLine));
			}
		}
		transScanner.close();
		//----------------------------------------------------------------
		
		//-------------------RUNS EACH TRANSACTION-----------------------
		int j = 0;
		while(j < arrayOfTransactions.size()){
			Transaction currentTransaction = arrayOfTransactions.get(j);
			File result = new File("./transaction_tests/actual result files/TransactionResult" + (j+1) + ".txt");
	    	File eResult = new File("./transaction_tests/expected result files/TransactionResult" + (j+1) + ".txt");
	    	FileOutputStream rof = new FileOutputStream(result);
	    	PrintStream resultPrint = new PrintStream(rof);

	    	System.setErr(resultPrint);
	    	testOutputs.add(Utilities.processTransaction(currentTransaction, arrayOfAccounts));
	    	
	    	resultFiles.add(result);
	    	expectedFiles.add(eResult);
	    	
	    	
	    	resetAccounts();
			j++;
			
		}
		//----------------------------------------------------------------
		
		//----------TESTS EACH TRANSACTION AGAINST EXPECTED OUTPUT--------
		for(int i=0; i<testOutputs.size(); i++){
			assertEquals("FAILED TEST", new Scanner(resultFiles.get(i)).useDelimiter("\\Z").next(), new Scanner(expectedFiles.get(i)).useDelimiter("\\Z").next());
		}
		//----------------------------------------------------------------
		
	}	
	//------------------RESETS THE ACCOUNTS ARRAY TO ORIGINAL-------------
	public void resetAccounts() throws FileNotFoundException{
		File masterAccountFile = new File("./transaction_tests/initial_master_accounts.txt");
		Scanner readAccounts = new Scanner(masterAccountFile);
	
		while(readAccounts.hasNextLine()){
			acctLine = readAccounts.nextLine();
		
			if(acctLine.length() == 44){
				arrayOfAccounts.add(new Account(acctLine));
			}
		}
		readAccounts.close();
	}
	//--------------------------------------------------------------------
}