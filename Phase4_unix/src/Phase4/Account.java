package Phase4;

public class Account {
	private String sAcctNum;
	private String sAcctHolderName;
	
	private char cAcctStatus;
	
	private double dBalance;
	
	public Account(String accountLine) {
		sAcctNum = accountLine.substring(0,5).trim();
		sAcctHolderName = accountLine.substring(6, 26).trim();
		cAcctStatus = accountLine.charAt(27);
		dBalance = Double.parseDouble(accountLine.substring(29));
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
	
	public void increaseBalance(double addAmt){
		dBalance+=addAmt;
	}
	
	public void decreaseBalance(double subAmt){
		dBalance-=subAmt;
	}
	
	public void setBalance(double newBalance){
		dBalance = newBalance;
	}

}
