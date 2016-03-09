package Phase4;

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
		
	}
	
	public static boolean deposit(Transaction t, Account a){
		
	}

	public static boolean create(Transaction t, Account a){
	
	}

	public static boolean delete(Transaction t, Account a){
	
	}
	
	public static boolean disable(Transaction t, Account a){
		
	}
	
	public static boolean changeplan(Transaction t, Account a){
		
	}
	
	public static boolean enable(Transaction t, Account a){
		
	}
	
	

}
