import React from "react";
import Modal from "react-modal";
import Button from "../Button";
import Input from "../Input";
import { useForm } from "react-hook-form";

const ProfileModal = ({ modalIsOpen, closeModal, submitForm }) => {
  const { register, handleSubmit, getValues } = useForm();

  const handleClick = async () => {
    const data = getValues();
    submitForm({ ...data});
    closeModal();
  };

  return (
    <Modal
      isOpen={modalIsOpen}
      onRequestClose={closeModal}
      contentLabel="Register account"
      className="modal"
    >
      <div className="row-between2">
        <div className="big-text">
          Edit account
        </div>
        <Button onClick={closeModal} className="icon-button">
          X
        </Button>
      </div>
      <div className="line" />
      <form>
        <Input label=" Name" placeholder="Your full name" {...register("name")}/>
        <Input label=" Phone" placeholder="Your phone number" {...register("phonenumber")}/>
        <Input label=" Email" placeholder="Your email address" {...register("email")}/>
        <Button type="button" onClick={handleSubmit(handleClick)}>
          Save
        </Button>
      </form>
    </Modal>
  );
};

export default ProfileModal;
