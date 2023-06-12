import java.rmi.registry.*;
import java.util.ArrayList;

//expected request format: java client <ip> <port number> <operation> <argument1> <argument2> <argument3>

public class Client {
    private static void invalidationMessage(){
        System.out.println("Invalid Auth Token");
    }

    public static void main(String[] args){
        try {
            //connect to the RMI registry
            Registry rmiRegistry = LocateRegistry.getRegistry(args[0], Integer.parseInt(args[1]));
            //get reference for remote object
            RRMessenger stub = (RRMessenger) rmiRegistry.lookup("RRMessenger");

            switch (args[2]) {
                case "1" -> { /*createAccount*/
                    int response = stub.createAccount(args[3]);
                    if (response > 0) System.out.println(response);
                    else if (response < 0) System.out.println("Invalid Username");
                    else System.out.println("Sorry, the user already exists");
                }
                case "2" -> { /*showAccounts*/
                    ArrayList<String> response = stub.showAccounts(Integer.parseInt(args[3]));
                    if (response == null) invalidationMessage();
                    else for (String line : response) System.out.println(line);
                }
                case "3" -> { /*sendMessage*/
                    String response = stub.sendMessage(Integer.parseInt(args[3]), args[4], args[5]);
                    System.out.println(response);
                }
                case "4" -> { /*showInbox*/
                    ArrayList<String> response = stub.showInbox(Integer.parseInt(args[3]));
                    if (response == null) invalidationMessage();
                    else if (response.isEmpty()) System.out.println("Inbox is empty");
                    else for (String line : response) System.out.println(line);
                }
                case "5" -> { /*readMessage*/
                    String response = stub.readMessage(Integer.parseInt(args[3]), Integer.parseInt(args[4]));
                    if (response == null) invalidationMessage();
                    else System.out.println(response);
                }
                case "6" -> { /*deleteMessage*/
                    String response = stub.deleteMessage(Integer.parseInt(args[3]), Integer.parseInt(args[4]));
                    if (response == null) invalidationMessage();
                    else System.out.println(response);
                }
                default -> System.out.println("Requested operation not recognized; Operations range from 1-6.");
            }
        }
        catch(NumberFormatException e){
            System.out.println("Unexpected request format; Please ensure arguments are given in the correct order.");
        }
        catch(ArrayIndexOutOfBoundsException e){
          System.out.println("Unexpected number of arguments; Please fill all required fields.");
        }
        catch(Exception e){
            System.err.println("Exception: " + e);
            e.printStackTrace();
        }
    }
}
