package Phase4;

import java.util.ArrayList;

public class TransactionProcessor {
	
	
	public static boolean withdrawal(Transaction t, Account a){
		double wdAmount = t.getFundsInvolved();
		double surcharge = a.getSurcharge();
		boolean completed;
		
		if(a.isValid(wdAmount + surcharge)){
			a.decreaseBalance(wdAmount + surcharge);
			a.incrementTransactionCount();
			completed = true;
		}
		else{
			System.err.println("ERROR: Transaction will leave negative account balance. Cannot complete."
					+ "\nTransacton: " + t.transAsString());
			completed = false;
		}
		return completed;
	}
	
	public static boolean transfer(Transaction t, Account a){
		//STUB
		return false;
	}
	
	public static boolean paybill(Transaction t, Account a){
		double payAmount = t.getFundsInvolved();
		double surcharge = a.getSurcharge();
		boolean completed = false;
		String[] companies = {
				"EC",
				"CQ",
				"TV",
		};
		String company = t.getMisc();
		boolean companyMatch = false;
		for (String comp : companies) {
			if(company.equals(comp))
			{
				companyMatch = true;
			}
		}
		if(!companyMatch){
			System.err.println("ERROR: Company not found. Cannot complete."
					+ "\nTransaction: " + t.transAsString());
			return completed;
		}
		//-----Only executed if the company was valid.-----
		if(a.isValid(payAmount + surcharge)){
			a.decreaseBalance(payAmount + surcharge);
			a.incrementTransactionCount();
			completed = true;
		}
		else{
			System.err.println("ERROR: Paying the bill will leave negative account balance. Cannot complete."
					+ "\nTransacton: " + t.transAsString());
			completed = false;
		}
		return completed;
	}
	
	public static boolean deposit(Transaction t, Account a){
		double depAmount = t.getFundsInvolved();
		double surcharge = a.getSurcharge();
		boolean completed;
		
		if(a.isValid(depAmount - surcharge)){
			a.increaseBalance(depAmount - surcharge);
			a.incrementTransactionCount();
			completed = true;
		}
		else{
			System.err.println("ERROR: Depositing will leave negative account balance. Wow, you're really depositing something small. Cannot complete."
					+ "\nTransacton: " + t.transAsString());
			completed = false;
		}
		return completed;
	}

	public static boolean create(Transaction t, ArrayList<Account> a){
		boolean completed = false;
		for (int i = 0; i < a.size(); i++) {
			if(t.getAccountNumber().equals(a.get(i).getNumber())){
				System.err.println("ERROR: Account already exists, cannot use the same number twice."
						+ "\nTransaction: " + t.transAsString());
				return completed;
			}
		}	
		//Only executed if account number does not exist
		System.out.println("This prototype autogenerates a new account number, and disregards the transaction's provided number."
				+ "\nIf the frontend is changed in the future, this can be modified easily.");
		String newAcctNum = Utilities.createNewAccountNumber(a);
		a.add(new Account(newAcctNum, t.getName()));
		completed = true;
		return completed;
	}

	public static boolean delete(Transaction t, Account a, ArrayList<Account> allAccts){
		String sToBeDeleted = t.getAccountNumber();
		boolean completed = false;
		for (int i = 0; i < allAccts.size(); i++) {
			if(allAccts.get(i).getNumber().equals(sToBeDeleted)){
				allAccts.remove(i);
				completed = true;
			}
		}
		if(!completed){
			System.err.println("ERROR: Account not found, cannot complete transaction."
					+ "\nTransaction: " + t.transAsString());
		}
		return completed;
	}
	
	public static boolean disable(Transaction t, Account a){
		a.setStatus('D');
		return true;
	}
	
	public static boolean changeplan(Transaction t, Account a){
		boolean done;		
		if(a.getPlan() == 'S'){
			a.setPlan('N');
			done = true;
		}
		else{
			a.setPlan('S');
			done = true;
		}
		return done;
	}
	
	public static boolean enable(Transaction t, Account a){
		a.setStatus('A');
		return true;
	}
	
	

}
