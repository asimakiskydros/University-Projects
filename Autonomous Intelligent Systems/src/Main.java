import javax.vecmath.*;
import simbad.gui.*;
import simbad.sim.*;

public class Main {
    public static void main(String[] args){
        EnvironmentDescription env = new EnvironmentDescription();

        // set up lights
        env.light1IsOn = true;
        env.light2IsOn = false;
        env.light1SetPosition(0, 2, -9);
        env.light2SetPosition(0, 2, -9);

        //add obstacles
        convex(env);
        //convex2(env);
        //concave(env);

        // add robot
        env.add(new MyRobot(new Vector3d(0, 0, 8), "Skynet"));
        new Simbad(env, false);
    }

    /**
     * Summon a wide square and a long rectangle.
     * @param env the environment
     * @author tonyloudis
     */
    static void convex(EnvironmentDescription env){
        env.add(new Box(new Vector3d(1,0,1), new Vector3f(5,1,5), env));
        env.add(new Box(new Vector3d(1,0,-5),new Vector3f(10,1,2),env));
    }

    /**
     * Summon a rounded rectangle and a small square.
     * @param env the environment
     * @author tonyloudis
     */
    static void convex2(EnvironmentDescription env){
        env.add(new Box(new Vector3d(0,0,3), new Vector3f(5,1,5),env));
        env.add(new Box(new Vector3d(2.75,0,3), new Vector3f(0.5f,1,4),env));
        env.add(new Box(new Vector3d(3.25,0,3), new Vector3f(0.5f,1,3),env));
        env.add(new Box(new Vector3d(-2.75,0,3), new Vector3f(0.5f,1,4),env));
        env.add(new Box(new Vector3d(-3.25,0,3), new Vector3f(0.5f,1,3),env));
        env.add(new Box(new Vector3d(0,0,-4), new Vector3f(2,1,2),env));
    }

    /**
     * Summon a giant reversed L.
     * @param env the environment
     * @author tonyloudis
     */
    static void concave(EnvironmentDescription env){
        env.add(new Box(new Vector3d(6,0,0),new Vector3f(2,1,10),env));
        env.add(new Box(new Vector3d(1,0,-5),new Vector3f(12,1,2),env));
    }
}
