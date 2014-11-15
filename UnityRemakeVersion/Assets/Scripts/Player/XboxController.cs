using UnityEngine;
using System.Collections;

public class XboxController : MonoBehaviour {

	public AudioSource walkingSound;
	public AudioSource idleSound;
	
	private Animator animator;
	private Heads heads;

	public float speed = 0.3f;
	
	bool canMove = true;
	bool canJump = true;
	bool canMove_left = true;
	bool canMove_right = true;
	float horizontal;

	float dt;
	
	// Use this for initialization
	void Start()
	{
		heads = this.GetComponent<Heads>();
		animator = this.GetComponent<Animator>();

		walkingSound.loop = true;
		idleSound.loop = true;
	}
	
	// Update is called once per frame
	void Update()
	{
		if(Input.GetButtonDown("MainMenu") || Input.GetKeyDown(KeyCode.Escape))
		{
			Application.LoadLevel("MainMenu");
		}

		if(canMove)
		{
			horizontal = Input.GetAxis("Horizontal");
			
			if(Input.GetButtonDown("Jump") && canJump)
			{
				rigidbody2D.AddForce(new Vector3(0,300,0));
				rigidbody2D.velocity = Vector2.zero;
			}
			
			RaycastHit2D hit = Physics2D.Raycast(transform.position, -Vector2.up,0.5f);
			Debug.DrawRay(transform.position,-Vector2.up * 0.5f,Color.blue);
			
			if (hit.collider != null) 
				canJump = true;
			else canJump = false;
		}
	}	

	void FixedUpdate()
	{
		#region LEFT AND RIGHT MOVEMENT

		if(canMove)
		{
			if (horizontal > 0 && canMove_right)
			{
				animator.SetBool ("Idle", false);
				animator.SetBool("GoingRight", true);
				heads.MoveRight(transform.position);

				rigidbody2D.velocity = new Vector2(0,rigidbody2D.velocity.y);

				transform.position += new Vector3(horizontal * speed / 10,0,0);
			}
			else if (horizontal < 0 && canMove_left)
			{
				animator.SetBool ("Idle", false);
				animator.SetBool("GoingRight", false);
				heads.MoveLeft(transform.position);

				rigidbody2D.velocity = new Vector2(0,rigidbody2D.velocity.y);

				transform.position -= new Vector3(-horizontal * speed / 10,0,0);
			}
			else 
			{
				animator.SetBool ("Idle", true);
				heads.Idle(transform.position);
			}

			if(horizontal != 0)
			{
				if(idleSound.volume > 0)
					idleSound.volume -= Time.deltaTime / 3;
				else
					idleSound.Stop ();

				if(walkingSound.volume < 1)
					walkingSound.volume += Time.deltaTime / 3;

				if(!walkingSound.isPlaying)
					walkingSound.Play();
			}
			else
			{
				if(walkingSound.volume > 0)
					walkingSound.volume -= Time.deltaTime / 3;
				else
					walkingSound.Stop ();

				if(idleSound.volume < 1)
					idleSound.volume += Time.deltaTime / 3;

				if(!idleSound.isPlaying)
					idleSound.Play();
			}
		}
		
		#endregion
	}
}



















