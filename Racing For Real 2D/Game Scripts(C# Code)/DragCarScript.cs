using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DragCarScript : MonoBehaviour
{
    public GameObject smoke;
    public GameObject nitroSmoke;

    public static float carSpeed;

    private float carTopSpeed;
    private float carAcceleration;
    private Rigidbody2D carBody;
    Vector2 carVelocity;
    private static int gearNr;
    public static int currentGear;
    public static float nitro;
    public static float rpm;
    private int optimalGear;
    private List<float> minSpeedPerGear = new List<float>();
    private List<float> maxSpeedPerGear = new List<float>();

    void Start()
    {
        carBody = GetComponent<Rigidbody2D>();
        carSpeed = 0;
        smoke.SetActive(true);
        carTopSpeed = 50;
        carAcceleration = 3;
        currentGear = 0;
        optimalGear = 0;
        gearNr = 6;
        rpm = 0;
        nitro = 100;
        for(int i = 1; i <= gearNr; i++)
        {
            minSpeedPerGear.Add(carTopSpeed * (i-1));
            maxSpeedPerGear.Add(carTopSpeed * i);
        }

    }
    void FixedUpdate()
    {
        if(!DragRaceLogic.finish)
        {
            if(Input.GetKey(KeyCode.N) && nitro > 0 && carSpeed > 0)
            {
                carAcceleration = 6;
                if(currentGear == 6)
                    carTopSpeed = 60;
                nitro -= 1;
                nitroSmoke.SetActive(true);
            }
            else
            {
                if(carAcceleration == 6)
                {
                    nitroSmoke.SetActive(false);
                    carAcceleration = 3;
                }
                if(carTopSpeed == 60)
                    carTopSpeed = 50;
            }
            if(currentGear != 0)
            {
                rpm = 100.0f - (carTopSpeed * currentGear - carSpeed);
                for(int i = 1; i <= gearNr; i++)
                {
                    if(carSpeed <= maxSpeedPerGear[i-1] && carSpeed >= minSpeedPerGear[i-1])
                        optimalGear = i;
                }
            }
            else if(carSpeed != 0)
                rpm = 80;
            if(rpm > 100 && carSpeed != 0)
                rpm = 100;
            if(rpm < 10 && carSpeed != 0)
                rpm = 10;
            carVelocity = carBody.velocity;
            carSpeed = carVelocity.magnitude;
            if(carSpeed < carTopSpeed * currentGear)
            {
                int speedFactor = 1;
                if(optimalGear != currentGear)
                    speedFactor = currentGear - optimalGear;
                carSpeed += carAcceleration / speedFactor;
                carBody.AddForce(transform.up * carAcceleration / speedFactor);
            }
            else if(carSpeed - carAcceleration > carTopSpeed * currentGear)
            {
                int speedFactor = 1;
                if(optimalGear != currentGear && currentGear != 0)
                    speedFactor = optimalGear - currentGear;
                carSpeed -= carAcceleration * 0.5f * speedFactor;
                carBody.AddForce(transform.up * -carAcceleration * 0.5f * speedFactor);
            }
            
            
            if(carSpeed != 0)
                smoke.SetActive(false);
        }
    }

    void Update()
    {
        if(!DragRaceLogic.finish)
        {
            if(Input.GetKeyDown(KeyCode.W) && currentGear < gearNr)
                currentGear++;
            if(Input.GetKeyDown(KeyCode.S) && currentGear > 0)
                currentGear--;
        }
    }

    void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.tag == "Finish")
            DragRaceLogic.lapsCounter++;
    }
}
