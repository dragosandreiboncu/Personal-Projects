import React from "react";
import Modal from "react-modal";
import Button from "../Button";
import { useForm } from "react-hook-form";

const RentModal = ({ modalIsOpen, closeModal, shelter, submitForm }) => {
  const { register, handleSubmit, getValues } = useForm();

  const handleClick = async () => {
    const data = getValues();
    submitForm({ shelterId: shelter.id});
    closeModal();
  };

  return (
    <Modal
      isOpen={modalIsOpen}
      onRequestClose={closeModal}
      contentLabel="Sign up"
      className="modal"
    >
      <form>
      <div className="text-2xl">You have successfully signed up for this shelter</div>
      <Button type="button" onClick={() => {handleSubmit(handleClick)}}>
        Ok
      </Button>
      </form>
    </Modal>
  );
};

export default RentModal;
