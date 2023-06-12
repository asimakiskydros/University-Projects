import java.io.Serializable;

public class Message implements Serializable {
    private boolean isRead;
    private final String sender;
    private final int messageID;
    private final String body;
    private final String receiver;

    public Message(boolean isRead, String sender, String receiver, int messageID, String body){
        this.isRead = isRead;
        this.sender = sender;
        this.receiver = receiver;
        this.messageID = messageID;
        this.body = body;
    }
    public void setStatus(boolean status){
        this.isRead = status;
    }
    public String getSender(){
        return this.sender;
    }
    public String getBody() {
        return this.body;
    }
    public boolean getStatus(){
        return this.isRead;
    }
    public int getMessageID() {
        return messageID;
    }
}
