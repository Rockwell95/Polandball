package Phase4;

import java.text.DecimalFormat;

public class Account {
	private String newMAcctString;
	private String newCAcctString;
	private String oldAcctString;
	private String sAcctNum;
	private String sAcctHolderName;
	private char cAcctStatus;
	private char cAcctPlan;
	private double dBalance;
	private int numTransactions;
	private double surcharge;

	private DecimalFormat df = new DecimalFormat("#.##");

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

	//Constructor for "create" transaction
	public Account(String acctNum, String acctName){
		sAcctNum = acctNum;
		sAcctHolderName = acctName;
		cAcctStatus = 'A';
		dBalance = 0;
		numTransactions = 0;
		cAcctPlan = 'N';
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
	//Creates a master string
	public String newAcctAsMasterString(){
		newMAcctString = sAcctNum + " " + Utilities.padSpaceRight(sAcctHolderName,20)+ " " + cAcctStatus + " "
				+ Utilities.padSpaceLeft(df.format(dBalance), 8) + " " + Utilities.padZeroesLeft("" + numTransactions, 4)
				+ " " + cAcctPlan;
		return newMAcctString;
	}
	//Creates a current string
	public String newAcctAsCurrentString(){
		newCAcctString = sAcctNum + " " + Utilities.padSpaceRight(sAcctHolderName,20)+ " " + cAcctStatus + " "
				+ Utilities.padSpaceLeft(df.format(dBalance), 8);
		return newCAcctString;
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

	public void setPlan(char plan){
		if(cAcctPlan == plan){
			System.err.println("ERROR: Account is already this type");
		}
		else if(plan != 'S' && plan != 'N'){
			System.err.println("ERROR: Account plan not recognized");
		}
		else if(cAcctPlan != plan){
			cAcctPlan = plan;
		}
	}

	public void setStatus(char newStatus){
		if(newStatus != 'A' && newStatus != 'D'){
			System.err.println("ERROR: status cannot be set to " + newStatus);
		}
		else{
			cAcctStatus = newStatus;
		}
	}

}
