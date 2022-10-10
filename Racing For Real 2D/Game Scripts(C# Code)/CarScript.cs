using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarScript : MonoBehaviour
{

    public float Top_Speed;
    public float Acceleration;
    public float Brake_Force;
    public float Handling;
    public GameObject smoke;
    public GameObject nitroSmoke;

    public static float carSpeed;
    private bool reverse;

    private float carTopSpeed;
    private float carAcceleration;
    private float carBrakeForce;
    private float carHandling;
    private Rigidbody2D carBody;
    public static float nitro;
    private float nitroCooldown;
    Vector3 carRotation;
    Vector2 carVelocity;

    void Start()
    {
        carBody = GetComponent<Rigidbody2D>();
        carTopSpeed = Top_Speed;
        carAcceleration = Acceleration;
        carBrakeForce= Brake_Force;
        carHandling = -Handling;
        carRotation = this.transform.eulerAngles;
        carSpeed = 0;
        nitro = 100;
        nitroCooldown = 3;
        nitroSmoke.SetActive(false);
        reverse = false;

    }
    void FixedUpdate()
    {
        carTopSpeed = Top_Speed;
        carAcceleration = Acceleration;
        carBrakeForce= Brake_Force;
        carHandling = -Handling;
        
        carRotation = this.transform.eulerAngles;
        carVelocity = carBody.velocity;
        carSpeed = carVelocity.magnitude;
        if(nitro < 100 && nitroCooldown <= 0)
            nitro += 0.1f;
        if(Input.GetKey(KeyCode.N) && !reverse && nitro > 0 && carSpeed > 0)
        {
            nitroSmoke.SetActive(true);
            nitroCooldown = 3;
            carAcceleration += 10;
            carTopSpeed += 30;
            nitro -= 0.75f;
        }
        else
        {
            nitroSmoke.SetActive(false);
            nitroCooldown -= Time.deltaTime;
            if(carAcceleration > Acceleration)
                carAcceleration = Acceleration;
            if(carTopSpeed > Top_Speed)
                carTopSpeed = Top_Speed;
        }

        if(Input.GetKey(KeyCode.W))
        {
            if(carSpeed == 0)
                reverse = false;
            if(reverse)
            {
                if(carSpeed < carBrakeForce)
                    carSpeed = 0;
                else 
                {
                    carSpeed -= carBrakeForce;
                    carBody.AddForce(transform.up * carBrakeForce);
                }
            }
            else if(carSpeed <= carTopSpeed)
            {
                carSpeed += carAcceleration ;
                carBody.AddForce(transform.up * carAcceleration);
            }
        }
        else if(Input.GetKey(KeyCode.S))
        {
            if(carSpeed == 0)
                reverse = true;
            if(!reverse)
            {
                if(carSpeed < carBrakeForce)
                    carSpeed = 0;
                else 
                {
                    carSpeed -= carBrakeForce;
                    carBody.AddForce(transform.up * -carBrakeForce);
                }
            }
            else if(carSpeed <= carTopSpeed * 0.25f)
            {
                carSpeed += carAcceleration ;
                carBody.AddForce(transform.up * -carAcceleration);
            }
        }
        if((Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.D)) && carSpeed != 0)
        {
            if(carSpeed > 100)
                smoke.SetActive(true);
            if(carSpeed < carBrakeForce)
                carSpeed = 0;
            else
                carSpeed -= carBrakeForce;
            if(reverse)
                carBody.AddForce(transform.up * carBrakeForce);
            else
                carBody.AddForce(transform.up * -carBrakeForce);
            if(reverse)
                carRotation.z += Input.GetAxis("Horizontal") * Time.deltaTime * carHandling * (-1);
            else
                carRotation.z += Input.GetAxis("Horizontal") * Time.deltaTime * carHandling;
            this.transform.eulerAngles = carRotation;
        }
        else if(carSpeed != 0)
            smoke.SetActive(false);
        if(carSpeed <= carBrakeForce)
            carBody.velocity = Vector2.zero;
        
        
    }
    void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.tag == "Finish")
        {
            if(RaceLogic.checkpointTaken && !RaceLogic.wrongDirection)
                RaceLogic.lapsCounter++;
            RaceLogic.checkpointTaken = false;
            RaceLogic.wrongDirection = false;
        }
        if(collision.gameObject.tag == "Checkpoint")
            RaceLogic.checkpointTaken = true;
        if(collision.gameObject.tag == "WrongDirection")
            if(!RaceLogic.checkpointTaken)
                RaceLogic.wrongDirection = true;
    }
}
