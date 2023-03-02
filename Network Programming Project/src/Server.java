import java.rmi.registry.*;

public class Server {
    public static void main(String[] args){
        try{
            //request port from user, if none given, assume 5000 as default (arbitrary choice)
            int port = args.length != 0 ? Integer.parseInt(args[0]) : 5000;

            //create the RMI registry on the given port
            Registry rmiRegistry = LocateRegistry.createRegistry(port);

            //register the object to the RMI registry
            rmiRegistry.rebind("RRMessenger", new RRMessengerRemote());
            System.out.println("Server start");
        }
        catch(NumberFormatException e){
            System.out.println("Unexpected port number; Startup failed.");
        }
        catch(Exception e){
            System.err.println("Exception: " + e);
            e.printStackTrace();
        }
    }
}