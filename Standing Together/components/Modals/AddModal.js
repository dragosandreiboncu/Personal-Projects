import React, { useState } from "react";
import Modal from "react-modal";
import { MdClose, MdCheck, MdExposurePlus1, MdExposureNeg1 } from "react-icons/md";
import Button from "../Button";
import Input from "../Input";
import { useForm } from "react-hook-form";

const AddModal = ({ modalIsOpen, closeModal, submitForm }) => {
  const { register, handleSubmit, getValues } = useForm();
  const [count, setCount] = useState(0);
  const [isChecked1, setShowmark1] = useState(false);
  const [isChecked2, setShowmark2] = useState(false);
  const [isChecked3, setShowmark3] = useState(false);

  const handleClick = async () => {
    const data = getValues();
    submitForm({ ...data});
    closeModal();
  };



  return (
    
    <Modal
      isOpen={modalIsOpen}
      onRequestClose={closeModal}
      contentLabel="Add shelter"
      className="modal"
      ariaHideApp={false}
    >
      <div className="row-between2">
        <div className="big-text">
          Add shelter
        </div>
        <Button onClick={closeModal}>
          X
        </Button>
      </div>
      <div className="line" />
      <form>
            <Input label="Address" placeholder="Add address" {...register("address")} />
            <Input type="text" disabled="disabled"
            label="Capacity"
            placeholder={count}
            {...register("capacity")}
            />
            <div className="row-between2">
              <Button type="button" onClick={() => setCount(count + 1)}>
                <MdExposurePlus1/>
              </Button>
              <Button type="button" onClick={() => {if(count>0) setCount(count - 1)}}>
                <MdExposureNeg1/>
              </Button>
          </div>

          <div className="row-between3">
            <Button type="button" onClick={() => setShowmark1(!isChecked1)} {...register("petallowed")}>
              Accepts pets
            </Button>
            {isChecked1 && (
            <div className="big-text text-green-buttons">
              <MdCheck/>
            </div>
            )}
            {!isChecked1 && (
              <div className="big-text text-green-buttons">
                <MdClose/>
              </div>
          )}
          </div>
          <div className="row-between3">
            <Button type="button" onClick={() => setShowmark2(!isChecked2)} {...register("foodprovided")}>
            Offers food
            </Button>
            {isChecked2 && (
            <div className="big-text text-green-buttons">
              <MdCheck/>
            </div>
            )}
            {!isChecked2 && (
              <div className="big-text text-green-buttons">
                <MdClose/>
              </div>
          )}
          </div>
          <div className="row-between3">
            <Button type="button" onClick={() => setShowmark3(!isChecked3)} {...register("firstaid")}>
            Offers first aid
            </Button>
            {isChecked3 && (
              <div className="big-text text-green-buttons">
                <MdCheck/>
              </div>
            )}
            {!isChecked3 && (
              <div className="big-text text-green-buttons">
                <MdClose/>
              </div>
            )}
          </div>
          <Button type="button" onClick={handleSubmit(handleClick)}>
            Add shelter
          </Button>
          
      </form>
    </Modal>
  );
};

export default AddModal;
