package Phase4;

public class Account {
	private String newAcctString;
	private String oldAcctString;
	private String sAcctNum;
	private String sAcctHolderName;
	private char cAcctStatus;
	private char cAcctPlan;
	private double dBalance;
	private int numTransactions;
	private double surcharge;
	
	public Account(String accountLine) {
		oldAcctString = accountLine;
		sAcctNum = accountLine.substring(0,5).trim();
		sAcctHolderName = accountLine.substring(6, 26).trim();
		cAcctStatus = accountLine.charAt(27);
		dBalance = Double.parseDouble(accountLine.substring(29,37));
		numTransactions = Integer.parseInt(accountLine.substring(38,42));
		cAcctPlan = accountLine.charAt(43);
		this.setSurcharge(cAcctPlan);
	}
	
	public String getName(){
		return sAcctHolderName;
	}
	
	public String getNumber(){
		return sAcctNum;
	}
	
	public char getStatus(){
		return cAcctStatus;
	}
	
	public double getBalance(){
		return dBalance;
	}
	
	public int getNumTransactions(){
		return numTransactions;
	}
	
	public char getPlan(){
		return cAcctPlan;
	}
	
	public void increaseBalance(double addAmt){
		dBalance+=addAmt;
	}
	
	public void decreaseBalance(double subAmt){
		dBalance-=subAmt;
	}
	
	public boolean isValid(double subAmt){
		if(dBalance - subAmt >= 0){
			return true;
		}
		else{
			return false;
		}
	}
	public void incrementTransactionCount(){
		numTransactions++;
	}
	public void setBalance(double newBalance){
		dBalance = newBalance;
	}
	
	public String newAcctAsString(){
		newAcctString = sAcctNum + " " + Utilities.padSpaceRight(sAcctHolderName,20)+ " " + cAcctStatus + " "
				+ Utilities.padSpaceLeft("" + dBalance, 8) + Utilities.padZeroesLeft("" + numTransactions, 4);
		return newAcctString;
	}
	
	public String currentAcctAsString(){
		return oldAcctString;
	}
	
	public void setSurcharge(char plan){
		if(plan == 'S'){
			surcharge = 0.05;
		}
		else{
			surcharge = 0.10;
		}
	}
	
	public double getSurcharge(){
		return surcharge;
	}

}
