package Phase4;

import static org.junit.Assert.*;

import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Scanner;

import org.junit.Test;

public class TransactionTesting {

	@Test
	public void test(){
		Utilities test = new Utilities();
		ArrayList<Boolean> testOutputs = new ArrayList<Boolean>();
		String acctLine;
		String transactionLine;
		String fileName;
		
		//List of Accounts and Transactions
		ArrayList<Transaction> arrayOfTransactions = new ArrayList<Transaction>();
		ArrayList<Account> arrayOfAccounts = new ArrayList<Account>();
		
		ArrayList<File> resultFiles = new ArrayList<File>();
		
		
		try{
			File masterAccountFile = new File("master_accounts.txt");
			Scanner readAccounts = new Scanner(masterAccountFile);
			
			while(readAccounts.hasNextLine()){
				acctLine = readAccounts.nextLine();
			
				if(acctLine.length() == 44){
					arrayOfAccounts.add(new Account(acctLine));
				}
			}
			readAccounts.close();
		}
		catch(Exception e){
			System.out.println(e.getMessage());
		}
		
			
		try{
			File masterTransactionFile = new File("merged_master_transactions.txt");
			Scanner transScanner = new Scanner(masterTransactionFile);
				
			while(transScanner.hasNextLine()){
				transactionLine = transScanner.nextLine();
				
				if(transactionLine.length() == 41){
					arrayOfTransactions.add(new Transaction(transactionLine));
				}
			}
			
			transScanner.close();
		}	
		catch(Exception e){
			System.out.println(e.getMessage());
		}
		
		int j = 0;
		while(j < arrayOfTransactions.size()){
			Transaction currentTransaction = arrayOfTransactions.get(j);
			Account testAccount = Utilities.getAccountByNumber(currentTransaction.getAccountNumber(), arrayOfAccounts);
		   
		    try{
		    	File result = new File("./result files/TransactionResult" + (j+1) + ".txt");
		    	FileOutputStream rof = new FileOutputStream(result);
		    	PrintStream resultPrint = new PrintStream(rof);
	
		    	System.setErr(resultPrint);
		    	testOutputs.add(test.processTransaction(currentTransaction, arrayOfAccounts));
		    	
		    	resultFiles.add(result);
		    }
		    catch(Exception e){
		    	System.out.println(e.getMessage());
		    }
			j++;
		}
		
		for(int i=0; i<testOutputs.size(); i++){
			assertEquals(testOutputs.get(i), true);
		}
	}	
}